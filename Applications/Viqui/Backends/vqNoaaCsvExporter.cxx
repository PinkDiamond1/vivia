/*ckwg +5
 * Copyright 2018 by Kitware, Inc. All Rights Reserved. Please refer to
 * KITWARE_LICENSE.TXT for licensing information, or contact General Counsel,
 * Kitware, Inc., 28 Corporate Drive, Clifton Park, NY 12065.
 */

#include <QMessageBox>

#include <vgFileDialog.h>

#include <vvWriter.h>

#include "vqNoaaCsvExporter.h"

#include <fstream>

//-----------------------------------------------------------------------------
bool vqNoaaCsvExporter::exportResults(const QList<vvQueryResult>& results)
{
  // Get name of file to which results should be written
  QString selectedFilter;
  QString fileName = vgFileDialog::getSaveFileName(
                       0, "Save results...", QString(),
                       "NOAA CSV File (*.csv);;"
                       "All files (*)", &selectedFilter);
  if (fileName.isEmpty())
    return false;

  // Open output file
  std::ofstream file(fileName.toStdString());
  if (!file)
    {
    QString msg = "Unable to open file \"%1\" for writing";
    QMessageBox::critical(0, "Error writing file",
                          msg.arg(fileName));
    return false;
    }

  // Write the file
  file << "#track-id,"
       << "file-name,"
       << "image-index,"
       << "TL-x,"
       << "TL-y,"
       << "BR-x,"
       << "BR-y,"
       << "confidence,"
       << "fish-length,"
       << "{class-name,score},..."
       << std::endl;

  foreach (const auto result, results)
    {
    foreach (const auto track, result.Tracks)
      {
      bool first = true;
      foreach (const auto trackState, track.Trajectory)
        {
        file << track.Id.SerialNumber << ","
             << result.StreamId << ","
             << trackState.TimeStamp.FrameNumber << ","
             << trackState.ImageBox.TopLeft.X << ","
             << trackState.ImageBox.TopLeft.Y << ","
             << trackState.ImageBox.BottomRight.X << ","
             << trackState.ImageBox.BottomRight.Y << ","
             << result.RelevancyScore << ","
             << "0.0"; // We don't know the fish length yet

        if (first)
          {
          foreach (const auto classification, track.Classification)
            {
            file << "," << classification.first << "," << classification.second;
            }

          first = false;
          }
        }

        file << std::endl;
      }
    }

  // Done
  return true;
}

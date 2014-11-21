/*ckwg +5
 * Copyright 2013 by Kitware, Inc. All Rights Reserved. Please refer to
 * KITWARE_LICENSE.TXT for licensing information, or contact General Counsel,
 * Kitware, Inc., 28 Corporate Drive, Clifton Park, NY 12065.
 */

#ifndef __vvClipVideoRepresentation_h
#define __vvClipVideoRepresentation_h

// Qt includes.
#include <QObject>

#include <vgExport.h>

// VG includes.
#include "vtkVgVideoRepresentation0.h"

// Forward declarations.
class vtkVgEvent;
struct vtkVgVideoFrameData;

class VV_VTKWIDGETS_EXPORT vvClipVideoRepresentation
  : public QObject, public vtkVgVideoRepresentation0
{
  Q_OBJECT

public:
  // Description:
  // Define easy to use types.
  vtkVgClassMacro(vvClipVideoRepresentation);

  vtkTypeMacro(vvClipVideoRepresentation, vtkVgVideoRepresentation0);

  static vvClipVideoRepresentation* New();

  virtual void PrintSelf(ostream& os, vtkIndent indent);

  vtkSetMacro(AutoCenter, int);
  vtkGetMacro(AutoCenter, int);

  virtual void Update();

  virtual void AutoCenterUpate(const vtkVgVideoFrameData* frameData);

signals:
  void areaOfInterest(double*, double, double);

protected:
  int AutoCenter;

  double RegionsMaxWidth;
  double RegionsMaxHeight;

  vtkVgEvent* VGEventCached;

protected:
  vvClipVideoRepresentation();
  virtual ~vvClipVideoRepresentation();

  virtual void HandleModelError() {}
  virtual void HandleAnimationCueTickEvent();
private:
  // Not implemented.
  vvClipVideoRepresentation(const vvClipVideoRepresentation&);
  void operator= (const vvClipVideoRepresentation&);
};



#endif // __vvClipVideoRepresentation_h
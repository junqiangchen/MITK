/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#include "mitkTrackingTool.h"

#include "mitkTestingMacros.h"

#include <iostream>
#include <time.h>

/**Documentation
* NDIPassiveTool has a protected constructor and a protected itkFactorylessNewMacro
* so that only it's friend class NDITrackingDevice is able to instantiate
* tool objects. Therefore, we derive from NDIPassiveTool and add a
* public itkFactorylessNewMacro, so that we can instantiate and test the class
*/
class InternalTrackingToolTestClass : public mitk::TrackingTool
{
public:
  mitkClassMacro(InternalTrackingToolTestClass, TrackingTool);
  /** make a public constructor, so that the test is able
  *   to instantiate NDIPassiveTool
  */
  itkFactorylessNewMacro(Self)
  itkCloneMacro(Self)
protected:
  InternalTrackingToolTestClass() : mitk::TrackingTool()
  {
  }

public: //these static methods are only to structure the test
        //please see them seperated from the upper part of the class

static void TestTooltipFunctionality()
{
  mitk::TrackingTool::Pointer trackingTool = InternalTrackingToolTestClass::New().GetPointer();
  mitk::Point3D toolTipPos; mitk::FillVector3D(toolTipPos,1,1,1);
  mitk::Quaternion toolTipQuat = mitk::Quaternion(0,0,0,1);
  trackingTool->SetToolTip(toolTipPos,toolTipQuat);

  mitk::Point3D positionInput; mitk::FillVector3D(positionInput,5,6,7);

  trackingTool->SetPosition(positionInput);

  mitk::Point3D positionOutput;

  trackingTool->GetPosition(positionOutput);

  MITK_TEST_CONDITION(((positionOutput[0] == 6)&&
                       (positionOutput[0] == 6)&&
                       (positionOutput[0] == 6)&&
                       (positionOutput[0] == 6)),
                       "Testing tooltip definition."
                     );
}

static void TestModiciationTimeCorrectness()
{
  mitk::TrackingTool::Pointer tool = InternalTrackingToolTestClass::New().GetPointer();
  unsigned long mTime1 = tool->GetMTime();

  mitk::Point3D position1;
  mitk::FillVector3D(position1, 1.1, 2.2, 3.3);
  tool->SetPosition(position1);
  MITK_TEST_CONDITION( mTime1 < tool->GetMTime(),
                       "Testing MTime updated after initial position set" );

  mitk::Quaternion quat1 = mitk::Quaternion(0,0,0.70710678118654757,0.70710678118654757);
  tool->SetOrientation(quat1);
  MITK_TEST_CONDITION( mTime1 < tool->GetMTime(),
                       "Testing MTime updated after initial orientation set" );

  unsigned long mTime2 = tool->GetMTime();

  mitk::Point3D position2;
  mitk::FillVector3D(position2, 1.10001, 2.2, 3.3);
  tool->SetPosition(position2);
  MITK_TEST_CONDITION( mTime2 < tool->GetMTime(),
                       "Testing MTime updated after new position set" );

  unsigned long mTime3 = tool->GetMTime();

  mitk::Quaternion quat2 = mitk::Quaternion(0.0,
                                            0.0,
                                            0.70710678118654757,
                                            0.70710678118654757 + 0.00001);
  tool->SetOrientation(quat2);
  MITK_TEST_CONDITION( mTime3 < tool->GetMTime(),
                       "Testing MTime updated after new orientation set" );

  mitk::Point3D position3;
  mitk::FillVector3D(position3, 1.10002, 2.2, 3.3);
}
};

/**
 *  Simple example for a test for the class "TrackingTool".
 *
 *  argc and argv are the command line parameters which were passed to
 *  the ADD_TEST command in the CMakeLists.txt file. For the automatic
 *  tests, argv is either empty for the simple tests or contains the filename
 *  of a test image for the image tests (see CMakeLists.txt).
 */
int mitkInternalTrackingToolTest(int /* argc */, char* /*argv*/[])
{
  // always start with this!
  MITK_TEST_BEGIN("TrackingTool")

  InternalTrackingToolTestClass::TestTooltipFunctionality();
  InternalTrackingToolTestClass::TestModiciationTimeCorrectness();

  // always end with this!
  MITK_TEST_END();
}


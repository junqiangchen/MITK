/*=========================================================================
 
Program:   Medical Imaging & Interaction Toolkit
Module:    $RCSfile: mitkPropertyManager.cpp,v $
Language:  C++
Date:      $Date$
Version:   $Revision: 1.12 $
 
Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.
 
This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.
 
=========================================================================*/

#ifndef mitkErasePaintbrushTool_h_Included
#define mitkErasePaintbrushTool_h_Included

#include "mitkPaintbrushTool.h"

namespace mitk
{

 /**
  \brief Paintbrush tool for InteractiveSegmentation

  \sa FeedbackContourTool
  \sa ExtractImageFilter
  \sa OverwriteSliceImageFilter
  
  \ingroup Interaction
  \ingroup Reliver

  Simple paintbrush drawing tool. Right now there are only circular pens of varying size.
  
  This class specified only the drawing "color" for the super class PaintbrushTool.
  
  \warning Only to be instantiated by mitk::ToolManager.
  $Author: maleike $
*/
class MITKEXT_CORE_EXPORT ErasePaintbrushTool : public PaintbrushTool
{
  public:

    mitkClassMacro(ErasePaintbrushTool, PaintbrushTool);
    itkNewMacro(ErasePaintbrushTool);

    virtual const char** GetXPM() const;
    virtual const char* GetName() const;

  protected:

    ErasePaintbrushTool(); // purposely hidden
    virtual ~ErasePaintbrushTool();

};

} // namespace

#endif


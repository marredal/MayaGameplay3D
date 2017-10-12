//
// ==================================================================
// Copyright 2014 Autodesk, Inc.  All rights reserved.
// 
// This computer source code  and related  instructions and comments are
// the unpublished confidential and proprietary information of Autodesk,
// Inc. and are  protected  under applicable  copyright and trade secret
// law. They may not  be disclosed to, copied or used by any third party
// without the prior written consent of Autodesk, Inc.
// ==================================================================
//
//! \file templateTypes.h
//!
//! \brief List of SynColor template classes, types, parameters and transform
//!        directions.
//!        \sa SYNCOLOR::Template

#ifndef _SYNCOLOR_TEMPLATE_TYPES_H
#define _SYNCOLOR_TEMPLATE_TYPES_H

#include <synColor/synExport.h>
#include <synColor/synColorNamespace.h>

SYN_VISIBILITY_PUSH

namespace SYNCOLOR
{

  //! \brief List of template classes.
  //!
  //! The template class defines the group of transforms to use to
  //! for the various template types.  Currently, there is a single
  //! template class.
  //!
  //! \sa SYNCOLOR::loadNativeTemplate()
  //!
  enum TemplateClass
  {
    Maya = 0, //!< Templates for Maya.
    Flame     //!< Templates for Flame.
  };

  //! List of possible template parameters.
  //!
  //! \sa SYNCOLOR::Template::getParameter()
  //!
  enum TemplateParameterId
  {
    WorkingSpace = 0,  //!< Working color space parameter.
    ViewTransform,     //!< View transform parameter.
    InputSpace,        //!< Input color space parameter.
    MixingSpace,       //!< Mixing color space parameter.
    MixingEncoding     //!< Mixing space encoding representation (eg. RGB or HSV).
  };

  //! List of possible template parameters value key.
  //!
  //! \sa SYNCOLOR::TemplateParameter::getValueForKey
  //!
  enum TemplateParameterValueKey
  {
    NameKey = 0,      //!< Name.
    HierarchyKey,     //!< Hierarchy.
    UserFacingNameKey //!< User facing name.
  };

  //! \brief List of template types.
  //!
  //! \sa SYNCOLOR::loadNativeTemplate()
  //!
  enum TemplateType
  {
    ViewingTemplate = 0, //!< Viewing transform template.
    InputTemplate,       //!< Input to working space transform template.
    MixingTemplate       //!< Color mixing transform template.
  };

  //! \brief List of transform directions.
  //!
  //! Templates can create either input-to-output color space transforms (forward) or
  //! output-to-input color space transforms (reverse).
  //!
  //! \sa SYNCOLOR::Template::createTransform()
  //!
  enum TransformDirection
  {
    TransformForward = 0,  //!< Normal (forward) transform.
    TransformReverse       //!< Inverse (reverse) transform.
  };
}

SYN_VISIBILITY_POP

#endif //_SYNCOLOR_TEMPLATE_TYPES_H

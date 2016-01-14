#ifndef __sitksimpletransformix_hxx_
#define __sitksimpletransformix_hxx_

#include "sitkSimpleTransformix.h"
 
namespace itk {
  namespace simple {

template<typename TInputImage >
Image
SimpleTransformix::ExecuteInternal( void )
{
  typedef elastix::TransformixFilter< TInputImage > TransformixFilterType;
  typedef typename TransformixFilterType::Pointer   TransforimxFilterPointer;

  TransforimxFilterPointer transformixFilter = TransformixFilterType::New();

  if( !this->IsEmpty( this->m_InputImage ) )
  {
    transformixFilter->SetInputImage( static_cast< TInputImage* >( this->GetInputImage().GetITKBase() ) );
  }

  transformixFilter->SetInputPointSetFileName( this->GetInputPointSetFileName() );
  transformixFilter->SetComputeSpatialJacobian( this->GetComputeSpatialJacobian() );
  transformixFilter->SetComputeDeterminantOfSpatialJacobian( this->GetComputeDeterminantOfSpatialJacobian() );
  transformixFilter->SetComputeDeformationField( this->GetComputeDeformationField() );

  ParameterObjectPointer parameterObject = ParameterObjectType::New();
  parameterObject->SetParameterMap( this->m_TransformParameterMapVector );
  transformixFilter->SetTransformParameterObject( parameterObject );

  transformixFilter->SetOutputDirectory( this->GetOutputDirectory() );
  transformixFilter->SetLogFileName( this->GetLogFileName() );
  transformixFilter->SetLogToFile( this->GetLogToFile() );
  transformixFilter->SetLogToConsole( this->GetLogToConsole ());

  transformixFilter->Update();

  if( !this->IsEmpty( this->m_InputImage ) )
  {
    this->m_ResultImage = Image( transformixFilter->GetOutput() );
  }

  return this->m_ResultImage;
}


} // end namespace simple
} // end namespace itk

#endif // __sitksimpletransformix_hxx_
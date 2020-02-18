/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#include <iomanip>
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "itkLabelSetErodeImageFilter.h"

#include "read_info.cxx"

template< class MaskPixType, int dim >
int doErode(char *In, char *Out, int radius)
{
  using MaskImType = typename itk::Image< MaskPixType, dim >;

  // load
  using ReaderType = typename itk::ImageFileReader< MaskImType >;
  typename ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(In);
  try
    {
    reader->Update();
    }
  catch ( itk::ExceptionObject & excp )
    {
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
    }

  // Label dilation
  using FilterType = typename itk::LabelSetErodeImageFilter< MaskImType, MaskImType >;
  typename FilterType::Pointer filter = FilterType::New();
  filter->SetInput( reader->GetOutput() );
  filter->SetRadius(radius);
  filter->SetUseImageSpacing(true);
  using WriterType = typename itk::ImageFileWriter< MaskImType >;
  typename WriterType::Pointer writer = WriterType::New();
  writer->SetInput( filter->GetOutput() );
  writer->SetFileName(Out);
  try
    {
    writer->Update();
    }
  catch ( itk::ExceptionObject & excp )
    {
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}

/////////////////////////////////////////////

int itkLabelSetErodeTest(int argc, char *argv[])
{
  int dim1;

  itk::MultiThreaderBase::SetGlobalMaximumNumberOfThreads(1);
  itk::IOComponentEnum ComponentType;

  if ( argc != 4 )
    {
    std::cerr << "Usage: " << argv[0] << "inputimage radius outputimage" << std::endl;
    return ( EXIT_FAILURE );
    }

  if ( !readImageInfo(argv[1], &ComponentType, &dim1) )
    {
    std::cerr << "Failed to open " << argv[1] << std::endl;
    return ( EXIT_FAILURE );
    }

  int status = EXIT_FAILURE;
  switch ( dim1 )
    {
    case 2:
      status = doErode< unsigned char, 2 >( argv[1], argv[3], std::stoi(argv[2]) );
      break;
    case 3:
      status = doErode< unsigned char, 3 >( argv[1], argv[3], std::stoi(argv[2]) );
      break;
    default:
      std::cerr << "Unsupported dimension" << std::endl;
      return ( EXIT_FAILURE );
      break;
    }
  return status;
}

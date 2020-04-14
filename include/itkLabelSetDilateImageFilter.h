/*=========================================================================
 *
 *  Copyright NumFOCUS
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
#ifndef itkLabelSetDilateImageFilter_h
#define itkLabelSetDilateImageFilter_h

#include "itkLabelSetMorphBaseImageFilter.h"
#include "itkNumericTraits.h"

namespace itk
{
/**
 * \class LabelSetDilateImageFilter
 * \brief Class for binary morphological erosion of label images.
 *
 * This filter is threaded.
 *
 * \sa itkLabelSetDilateErodeImageFilter
 *
 * \ingroup LabelErodeDilate
 *
 * \author Richard Beare, Department of Medicine, Monash University,
 * Australia.  <Richard.Beare@monash.edu>
 **/
template <typename TInputImage, typename TOutputImage = TInputImage>
class ITK_EXPORT LabelSetDilateImageFilter : public LabelSetMorphBaseImageFilter<TInputImage, true, TOutputImage>
{
public:
  ITK_DISALLOW_COPY_AND_ASSIGN(LabelSetDilateImageFilter);

  /** Standard class type alias. */
  using Self = LabelSetDilateImageFilter;
  using Superclass = LabelSetMorphBaseImageFilter<TInputImage, true, TOutputImage>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(LabelSetDilateImageFilter, LabelSetMorphBaseImageFilter);

  /** Pixel Type of the input image */
  using InputImageType = TInputImage;
  using OutputImageType = TOutputImage;
  using PixelType = typename TInputImage::PixelType;
  using RealType = typename NumericTraits<PixelType>::FloatType;
  using OutputPixelType = typename TOutputImage::PixelType;
  using ScalarRealType = typename NumericTraits<PixelType>::ScalarRealType;

  /** Smart pointer type alias support.  */
  using InputImagePointer = typename TInputImage::Pointer;
  using InputImageConstPointer = typename TInputImage::ConstPointer;
  using InputSizeType = typename TInputImage::SizeType;
  using OutputSizeType = typename TOutputImage::SizeType;

  using OutputImageRegionType = typename OutputImageType::RegionType;

  /** Image dimension. */
  static constexpr unsigned int ImageDimension = TInputImage::ImageDimension;
  static constexpr unsigned int OutputImageDimension = TOutputImage::ImageDimension;
  static constexpr unsigned int InputImageDimension = TInputImage::ImageDimension;

protected:
  LabelSetDilateImageFilter() { this->DynamicMultiThreadingOff(); }
  ~LabelSetDilateImageFilter() override = default;

  void
  ThreadedGenerateData(const OutputImageRegionType & outputRegionForThread, ThreadIdType threadId) override;

private:
  using DistanceImageType = typename Superclass::DistanceImageType;
};
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkLabelSetDilateImageFilter.hxx"
#endif

#endif

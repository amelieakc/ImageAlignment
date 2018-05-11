  #ifndef itkImageRegistrationMethod_h
  #define itkImageRegistrationMethod_h
   
  #include "itkProcessObject.h"
  #include "itkImage.h"
  #include "itkImageToImageMetric.h" 
  #include "itkSingleValuedNonLinearOptimizer.h"
  #include "itkDataObjectDecorator.h"
    
  namespace itk
  { 
  template< typename TFixedImage, typename TMovingImage >
  class ITK_TEMPLATE_EXPORT ImageRegistrationMethod:public ProcessObject
  {
  public:
  ITK_DISALLOW_COPY_AND_ASSIGN(ImageRegistrationMethod);
    
  using Self = ImageRegistrationMethod;
  using Superclass = ProcessObject;
  using Pointer = SmartPointer< Self >;
  using ConstPointer = SmartPointer< const Self >;
    
  itkNewMacro(Self);
   
  itkTypeMacro(ImageRegistrationMethod, ProcessObject);
  
  using FixedImageType = TFixedImage;
  using FixedImageConstPointer = typename FixedImageType::ConstPointer;
 
  using MovingImageType = TMovingImage;
  using MovingImageConstPointer = typename MovingImageType::ConstPointer;
  
  using MetricType = ImageToImageMetric< FixedImageType, MovingImageType >;
  using MetricPointer = typename MetricType::Pointer;
  using FixedImageRegionType = typename MetricType::FixedImageRegionType;
  
  using TransformType = typename MetricType::TransformType;
  using TransformPointer = typename TransformType::Pointer;
  
  using TransformOutputType = DataObjectDecorator< TransformType >;
  using TransformOutputPointer = typename TransformOutputType::Pointer;
  using TransformOutputConstPointer = typename TransformOutputType::ConstPointer;
  
  using InterpolatorType = typename MetricType::InterpolatorType;
  using InterpolatorPointer = typename InterpolatorType::Pointer;
 
  using OptimizerType = SingleValuedNonLinearOptimizer;
  
  using ParametersType = typename MetricType::TransformParametersType;
  
  using DataObjectPointer = typename DataObject::Pointer;
  
  void SetFixedImage(const FixedImageType *fixedImage);
  itkGetConstObjectMacro(FixedImage, FixedImageType);
  
  void SetMovingImage(const MovingImageType *movingImage);
  itkGetConstObjectMacro(MovingImage, MovingImageType);
  
  itkSetObjectMacro(Optimizer,  OptimizerType);
  itkGetModifiableObjectMacro(Optimizer, OptimizerType);
 
  itkSetObjectMacro(Metric, MetricType);
  itkGetModifiableObjectMacro(Metric, MetricType);
  
  itkSetObjectMacro(Transform, TransformType);
  itkGetModifiableObjectMacro(Transform, TransformType);
 
  itkSetObjectMacro(Interpolator, InterpolatorType);
  itkGetModifiableObjectMacro(Interpolator, InterpolatorType);

  virtual void SetInitialTransformParameters(const ParametersType & param);

  itkGetConstReferenceMacro(InitialTransformParameters, ParametersType);
  
  itkGetConstReferenceMacro(LastTransformParameters, ParametersType);
 
  void SetFixedImageRegion(const FixedImageRegionType & region);

  itkGetConstReferenceMacro(FixedImageRegion, FixedImageRegionType);
 
  itkGetConstMacro(FixedImageRegionDefined, bool);
  
  itkSetMacro(FixedImageRegionDefined, bool);
 
  virtual void Initialize();
  
  const TransformOutputType * GetOutput() const;
  
  using DataObjectPointerArraySizeType = ProcessObject::DataObjectPointerArraySizeType;
  using Superclass::MakeOutput;
  DataObjectPointer MakeOutput(DataObjectPointerArraySizeType idx) override;
  
  ModifiedTimeType GetMTime() const override;
 
  protected:
  ImageRegistrationMethod();
  ~ImageRegistrationMethod() override {}
  void PrintSelf(std::ostream & os, Indent indent) const override;
  void  GenerateData() override;
  
  itkSetMacro(LastTransformParameters, ParametersType);
 
  /* Start the Optimization */
  void StartOptimization();
  
  private:
  MetricPointer m_Metric;
  OptimizerType::Pointer m_Optimizer;
  
  MovingImageConstPointer m_MovingImage;
  FixedImageConstPointer  m_FixedImage;
  
  TransformPointer m_Transform;
  InterpolatorPointer m_Interpolator;
   
  ParametersType m_InitialTransformParameters;
  ParametersType m_LastTransformParameters;
  
  bool m_FixedImageRegionDefined;
  FixedImageRegionType m_FixedImageRegion;
  };
  } // end namespace itk
   
  #ifndef ITK_MANUAL_INSTANTIATION
  #include "itkImageRegistrationMethod.hxx"
  #endif
  #endif

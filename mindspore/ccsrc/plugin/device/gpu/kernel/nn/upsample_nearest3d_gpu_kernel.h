/**
 * Copyright 2022 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MINDSPORE_CCSRC_BACKEND_KERNEL_COMPILER_GPU_NN_UPSAMPLE_NEAREST3D_GPU_KERNEL_H_
#define MINDSPORE_CCSRC_BACKEND_KERNEL_COMPILER_GPU_NN_UPSAMPLE_NEAREST3D_GPU_KERNEL_H_

#include <algorithm>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include "plugin/device/gpu/kernel/gpu_kernel.h"
#include "plugin/factory/ms_factory.h"

namespace mindspore {
namespace kernel {
class UpsampleNearest3dGpuKernelMod : public NativeGpuKernelMod {
 public:
  UpsampleNearest3dGpuKernelMod() = default;
  ~UpsampleNearest3dGpuKernelMod() override = default;
  bool Launch(const std::vector<AddressPtr> &inputs, const std::vector<AddressPtr> &workspace,
              const std::vector<AddressPtr> &outputs, void *cuda_stream) override {
    if (is_null_input_) {
      return true;
    }
    cuda_stream_ = cuda_stream;
    return kernel_func_(this, inputs, workspace, outputs);
  }

  bool Init(const BaseOperatorPtr &base_operator, const std::vector<KernelTensorPtr> &inputs,
            const std::vector<KernelTensorPtr> &outputs) override;

  int Resize(const BaseOperatorPtr &base_operator, const std::vector<KernelTensorPtr> &inputs,
             const std::vector<KernelTensorPtr> &outputs, const std::map<uint32_t, tensor::TensorPtr> &) override;

 protected:
  std::vector<KernelAttr> GetOpSupport() override;

 private:
  template <typename T>
  bool LaunchKernel(const std::vector<AddressPtr> &inputs, const std::vector<AddressPtr> &workspace,
                    const std::vector<AddressPtr> &outputs);

  using UpsampleNearest3dFunc = std::function<bool(UpsampleNearest3dGpuKernelMod *, const std::vector<AddressPtr> &,
                                                   const std::vector<AddressPtr> &, const std::vector<AddressPtr> &)>;

  bool GetUpsampleNearest3dAttr(const BaseOperatorPtr &base_operator);

  float Scaling(const size_t in_size, const size_t out_size, int idx);

  float Scaling(const float scale_value, int idx);

  void *cuda_stream_{nullptr};
  bool is_null_input_{false};
  std::vector<size_t> input_shape_;
  std::vector<size_t> output_shape_;
  std::vector<int64_t> output_volumetric_size_;
  std::vector<float> scale_factors_;
  UpsampleNearest3dFunc kernel_func_;
  static std::vector<std::pair<KernelAttr, UpsampleNearest3dFunc>> func_list_;
};
}  // namespace kernel
}  // namespace mindspore
#endif  // MINDSPORE_CCSRC_BACKEND_KERNEL_COMPILER_GPU_NN_UPSAMPLE_NEAREST3D_GPU_KERNEL_H_

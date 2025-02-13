mindspore.nn.Conv3d
=============================

.. py:class:: mindspore.nn.Conv3d(in_channels, out_channels, kernel_size, stride=1, pad_mode='same', padding=0, dilation=1, group=1, has_bias=False, weight_init='normal', bias_init='zeros', data_format='NCDHW')

    三维卷积层。

    对输入Tensor计算三维卷积，该Tensor的shape通常为 :math:`(N, C_{in}, D_{in}, H_{in}, W_{in})` ，其中 :math:`N` 为batch size， :math:`C_{in}` 是空间维度。:math:`D_{in}, H_{in}, W_{in}` 分别为特征层的深度、高度和宽度。对于每个batch中的Tensor，其shape为 :math:`(C_{in}, D_{in}, H_{in}, W_{in})` ，公式定义如下：

    .. math::
        \text{out}(N_i, C_{\text{out}_j}) = \text{bias}(C_{\text{out}_j}) +
        \sum_{k = 0}^{C_{in} - 1} \text{ccor}({\text{weight}(C_{\text{out}_j}, k), \text{X}(N_i, k)})

    其中，:math:`ccor` 为 `cross-correlation <https://en.wikipedia.org/wiki/Cross-correlation>`_ ， :math:`C_{in}` 为输入空间维度， :math:`out_{j}` 对应输出的第 :math:`j` 个空间维度，:math:`j` 的范围在 :math:`[0，C_{out}-1]` 内，
    :math:`\text{weight}(C_{\text{out}_j}, k)` 是shape为 :math:`(\text{kernel_size[0]}, \text{kernel_size[1]}, \text{kernel_size[2]})` 的卷积核切片，其中 :math:`\text{kernel_size[0]}` , :math:`\text{kernel_size[1]}` 和 :math:`\text{kernel_size[2]}` 是卷积核的深度、高度和宽度。 :math:`\text{bias}` 为偏置参数， :math:`\text{X}` 为输入Tensor。
    完整卷积核的shape为 :math:`(C_{out}, C_{in} / \text{group}, \text{kernel_size[0]}, \text{kernel_size[1]}, \text{kernel_size[2]})` ，其中 `group` 是在空间维度上分割输入 `x` 的组数。
    详细介绍请参考论文 `Gradient Based Learning Applied to Document Recognition <http://vision.stanford.edu/cs598_spring07/papers/Lecun98.pdf>`_ 。

    **参数：**

    - **in_channels** (int) - Conv3d层输入Tensor的空间维度。
    - **out_channels** (int) - Conv3d层输出Tensor的空间维度。
    - **kernel_size** (Union[int, tuple[int]]) - 指定三维卷积核的深度、高度和宽度。数据类型为int或包含三个整数的tuple。一个整数表示卷积核的深度、高度和宽度均为该值该值。包含三个整数的tuple分别表示卷积核的深度、高度和宽度。
    - **stride** (Union[int, tuple[int]]) - 三维卷积核的移动步长。数据类型为整型或三个整型的tuple。一个整数表示在深度、高度和宽度方向的移动步长均为该值。三个整数的tuple分别表示在深度、高度和宽度方向的移动步长。默认值：1。
    - **pad_mode** (str) - 指定填充模式。可选值为"same"、"valid"、"pad"。默认值："same"。

      - same：输出的深度、高度和宽度分别与输入整除 `stride` 后的值相同。若设置该模式，`padding` 的值必须为0。
      - valid：在不填充的前提下返回有效计算所得的输出。不满足计算的多余像素会被丢弃。如果设置此模式，则 `padding` 的值必须为0。
      - pad：对输入进行填充。 在输入的深度、高度和宽度方向上填充 `padding` 大小的0。如果设置此模式， `padding` 必须大于或等于0。

    - **padding** (Union(int, tuple[int])) - 输入的深度、高度和宽度方向上填充的数量。数据类型为int或包含6个整数的tuple。如果 `padding` 是一个整数，则前部、后部、顶部，底部，左边和右边的填充都等于 `padding` 。如果 `padding` 是6个整数的tuple，则前部、尾部、顶部、底部、左边和右边的填充分别等于填充padding[0]、padding[1]、padding[2]、padding[3]、padding[4]和padding[5]。值应该要大于等于0，默认值：0。
    - **dilation** (Union[int, tuple[int]]) - 三维卷积核膨胀尺寸。数据类型为int或三个整数的tuple。若取值k > 1，则kernel对每k个元素进行采样。在深度、高度和宽度方向上的取值范围分别为[1, D]、[1, H]和[1, W]。默认值：1。
    - **group** (int) - 将过滤器拆分为组， `in_channels` 和 `out_channels` 必须可被 `group` 整除。默认值：1。当前仅支持1。
    - **has_bias** (bool) - Conv3d层是否添加偏置参数。默认值：False。
    - **weight_init** (Union[Tensor, str, Initializer, numbers.Number]) - 权重参数的初始化方法。它可以是Tensor，str，Initializer或numbers.Number。当使用str时，可选"TruncatedNormal"，"Normal"，"Uniform"，"HeUniform"和"XavierUniform"分布以及常量"One"和"Zero"分布的值，可接受别名"xavier_uniform"，"he_uniform"，"ones"和"zeros"。上述字符串大小写均可。更多细节请参考Initializer的值。默认值："normal"。
    - **bias_init** (Union[Tensor, str, Initializer, numbers.Number]) - 偏置参数的初始化方法。可以使用的初始化方法与"weight_init"相同。更多细节请参考Initializer的值。默认值："zeros"。
    - **data_format** (str) - 数据格式的可选值。目前仅支持"NCDHW"。

    **输入：**

    - **x** (Tensor) - shape为 :math:`(N, C_{in}, D_{in}, H_{in}, W_{in})` 的Tensor。目前输入数据类型只支持float16和float32。

    **输出：**

    Tensor，shape为 :math:`(N, C_{out}, D_{out}, H_{out}, W_{out})` 。

    pad_mode为"same"时：

    .. math::
        \begin{array}{ll} \\
            D_{out} ＝ \left \lfloor{\frac{D_{in}}{\text{stride[0]}} + 1} \right \rfloor \\
            H_{out} ＝ \left \lfloor{\frac{H_{in}}{\text{stride[1]}} + 1} \right \rfloor \\
            W_{out} ＝ \left \lfloor{\frac{W_{in}}{\text{stride[2]}} + 1} \right \rfloor \\
        \end{array}

    pad_mode为"valid"时：

    .. math::
        \begin{array}{ll} \\
            D_{out} ＝ \left \lfloor{\frac{D_{in} - \text{dilation[0]} \times (\text{kernel_size[0]} - 1) }
            {\text{stride[0]}} + 1} \right \rfloor \\
            H_{out} ＝ \left \lfloor{\frac{H_{in} - \text{dilation[1]} \times (\text{kernel_size[1]} - 1) }
            {\text{stride[1]}} + 1} \right \rfloor \\
            W_{out} ＝ \left \lfloor{\frac{W_{in} - \text{dilation[2]} \times (\text{kernel_size[2]} - 1) }
            {\text{stride[2]}} + 1} \right \rfloor \\
        \end{array}

    pad_mode为"pad"时：

    .. math::
        \begin{array}{ll} \\
            D_{out} ＝ \left \lfloor{\frac{D_{in} + padding[0] + padding[1] - (\text{dilation[0]} - 1) \times
            \text{kernel_size[0]} - 1 }{\text{stride[0]}} + 1} \right \rfloor \\
            H_{out} ＝ \left \lfloor{\frac{H_{in} + padding[2] + padding[3] - (\text{dilation[1]} - 1) \times
            \text{kernel_size[1]} - 1 }{\text{stride[1]}} + 1} \right \rfloor \\
            W_{out} ＝ \left \lfloor{\frac{W_{in} + padding[4] + padding[5] - (\text{dilation[2]} - 1) \times
            \text{kernel_size[2]} - 1 }{\text{stride[2]}} + 1} \right \rfloor \\
        \end{array}

    **异常：**

    - **TypeError** - `in_channels` 、 `out_channels` 或 `group` 不是int。
    - **TypeError** - `kernel_size` 、 `stride` 、 `padding` 或 `dilation` 既不是int也不是tuple。
    - **ValueError** - `out_channels` 、 `kernel_size` 、 `stride` 或 `dilation` 小于1。
    - **ValueError** - `padding` 小于0。
    - **ValueError** - `pad_mode` 不是"same"，"valid"或"pad"。
    - **ValueError** - `padding` 是长度不等于6的tuple。
    - **ValueError** - `pad_mode` 不等于"pad"且 `padding` 不等于(0, 0, 0, 0, 0, 0)。
    - **ValueError** - `data_format` 不是"NCDHW"。

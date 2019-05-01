/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * License); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * AS IS BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * Copyright (c) 2019, Open AI Lab
 * Author: ruizhang@openailab.com
 */

#ifndef __REF_NORMAL_KERNEL_H__
#define __REF_NORMAL_KERNEL_H__

#include <stdint.h>
#include <math.h>

#include "compiler_fp16.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ref_normalize_param
{
    int input_n;
    int input_h;
    int input_w;
    int input_c;
    int across_spatial;
    int channel_shared;
    int layout;
    float in_scale;
    int in_zero;
    float out_scale;
    int out_zero;
    float scale_scale;
    int scale_zero;
};

typedef int (*ref_normalize_kernel_t)(void *input,void * output,void* scale,const ref_normalize_param* param);


#ifdef CONFIG_KERNEL_FP32
#include "ref_normalize_fp32.c"
#endif

#ifdef CONFIG_KERNEL_FP16
#include "ref_normalize_fp16.c"
#endif

#ifdef CONFIG_KERNEL_INT8
#include "ref_normalize_int8.c"
#endif

#ifdef CONFIG_KERNEL_UINT8
#include "ref_normalize_uint8.c"
#endif


#ifdef __cplusplus
}
#endif

#endif

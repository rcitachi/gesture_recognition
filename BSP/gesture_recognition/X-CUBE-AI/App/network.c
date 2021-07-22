/**
  ******************************************************************************
  * @file    network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Tue Jul 20 21:37:20 2021
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */


#include "network.h"

#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "layers.h"



#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#define AI_TOOLS_VERSION_MAJOR 5
#define AI_TOOLS_VERSION_MINOR 2
#define AI_TOOLS_VERSION_MICRO 0


#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#define AI_TOOLS_API_VERSION_MAJOR 1
#define AI_TOOLS_API_VERSION_MINOR 3
#define AI_TOOLS_API_VERSION_MICRO 0

#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_network
 
#undef AI_NETWORK_MODEL_SIGNATURE
#define AI_NETWORK_MODEL_SIGNATURE     "3dbd9eef1b0049b4c0239096a5e669a3"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     "(rev-5.2.0)"
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Tue Jul 20 21:37:20 2021"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_NETWORK_N_BATCHES
#define AI_NETWORK_N_BATCHES         (1)

/**  Forward network declaration section  *************************************/
AI_STATIC ai_network AI_NET_OBJ_INSTANCE;


/**  Forward network array declarations  **************************************/
AI_STATIC ai_array conv2d_5_scratch1_array;   /* Array #0 */
AI_STATIC ai_array conv2d_5_scratch0_array;   /* Array #1 */
AI_STATIC ai_array conv2d_3_scratch1_array;   /* Array #2 */
AI_STATIC ai_array conv2d_3_scratch0_array;   /* Array #3 */
AI_STATIC ai_array conv2d_1_scratch1_array;   /* Array #4 */
AI_STATIC ai_array conv2d_1_scratch0_array;   /* Array #5 */
AI_STATIC ai_array dense_10_bias_array;   /* Array #6 */
AI_STATIC ai_array dense_10_weights_array;   /* Array #7 */
AI_STATIC ai_array dense_9_bias_array;   /* Array #8 */
AI_STATIC ai_array dense_9_weights_array;   /* Array #9 */
AI_STATIC ai_array dense_8_bias_array;   /* Array #10 */
AI_STATIC ai_array dense_8_weights_array;   /* Array #11 */
AI_STATIC ai_array conv2d_5_bias_array;   /* Array #12 */
AI_STATIC ai_array conv2d_5_weights_array;   /* Array #13 */
AI_STATIC ai_array conv2d_3_bias_array;   /* Array #14 */
AI_STATIC ai_array conv2d_3_weights_array;   /* Array #15 */
AI_STATIC ai_array conv2d_1_bias_array;   /* Array #16 */
AI_STATIC ai_array conv2d_1_weights_array;   /* Array #17 */
AI_STATIC ai_array conv2d_input_output_array;   /* Array #18 */
AI_STATIC ai_array conversion_0_output_array;   /* Array #19 */
AI_STATIC ai_array conv2d_1_output_array;   /* Array #20 */
AI_STATIC ai_array conv2d_3_output_array;   /* Array #21 */
AI_STATIC ai_array conv2d_5_output_array;   /* Array #22 */
AI_STATIC ai_array dense_8_output_array;   /* Array #23 */
AI_STATIC ai_array dense_9_output_array;   /* Array #24 */
AI_STATIC ai_array dense_10_output_array;   /* Array #25 */
AI_STATIC ai_array dense_10_fmt_output_array;   /* Array #26 */
AI_STATIC ai_array nl_11_output_array;   /* Array #27 */
AI_STATIC ai_array nl_11_fmt_output_array;   /* Array #28 */


/**  Forward network tensor declarations  *************************************/
AI_STATIC ai_tensor conv2d_5_scratch1;   /* Tensor #0 */
AI_STATIC ai_tensor conv2d_5_scratch0;   /* Tensor #1 */
AI_STATIC ai_tensor conv2d_3_scratch1;   /* Tensor #2 */
AI_STATIC ai_tensor conv2d_3_scratch0;   /* Tensor #3 */
AI_STATIC ai_tensor conv2d_1_scratch1;   /* Tensor #4 */
AI_STATIC ai_tensor conv2d_1_scratch0;   /* Tensor #5 */
AI_STATIC ai_tensor dense_10_bias;   /* Tensor #6 */
AI_STATIC ai_tensor dense_10_weights;   /* Tensor #7 */
AI_STATIC ai_tensor dense_9_bias;   /* Tensor #8 */
AI_STATIC ai_tensor dense_9_weights;   /* Tensor #9 */
AI_STATIC ai_tensor dense_8_bias;   /* Tensor #10 */
AI_STATIC ai_tensor dense_8_weights;   /* Tensor #11 */
AI_STATIC ai_tensor conv2d_5_bias;   /* Tensor #12 */
AI_STATIC ai_tensor conv2d_5_weights;   /* Tensor #13 */
AI_STATIC ai_tensor conv2d_3_bias;   /* Tensor #14 */
AI_STATIC ai_tensor conv2d_3_weights;   /* Tensor #15 */
AI_STATIC ai_tensor conv2d_1_bias;   /* Tensor #16 */
AI_STATIC ai_tensor conv2d_1_weights;   /* Tensor #17 */
AI_STATIC ai_tensor conv2d_input_output;   /* Tensor #18 */
AI_STATIC ai_tensor conversion_0_output;   /* Tensor #19 */
AI_STATIC ai_tensor conv2d_1_output;   /* Tensor #20 */
AI_STATIC ai_tensor conv2d_3_output;   /* Tensor #21 */
AI_STATIC ai_tensor conv2d_5_output;   /* Tensor #22 */
AI_STATIC ai_tensor conv2d_5_output0;   /* Tensor #23 */
AI_STATIC ai_tensor dense_8_output;   /* Tensor #24 */
AI_STATIC ai_tensor dense_9_output;   /* Tensor #25 */
AI_STATIC ai_tensor dense_10_output;   /* Tensor #26 */
AI_STATIC ai_tensor dense_10_fmt_output;   /* Tensor #27 */
AI_STATIC ai_tensor nl_11_output;   /* Tensor #28 */
AI_STATIC ai_tensor nl_11_fmt_output;   /* Tensor #29 */


/**  Forward network tensor chain declarations  *******************************/
AI_STATIC_CONST ai_tensor_chain conversion_0_chain;   /* Chain #0 */
AI_STATIC_CONST ai_tensor_chain conv2d_1_chain;   /* Chain #1 */
AI_STATIC_CONST ai_tensor_chain conv2d_3_chain;   /* Chain #2 */
AI_STATIC_CONST ai_tensor_chain conv2d_5_chain;   /* Chain #3 */
AI_STATIC_CONST ai_tensor_chain dense_8_chain;   /* Chain #4 */
AI_STATIC_CONST ai_tensor_chain dense_9_chain;   /* Chain #5 */
AI_STATIC_CONST ai_tensor_chain dense_10_chain;   /* Chain #6 */
AI_STATIC_CONST ai_tensor_chain dense_10_fmt_chain;   /* Chain #7 */
AI_STATIC_CONST ai_tensor_chain nl_11_chain;   /* Chain #8 */
AI_STATIC_CONST ai_tensor_chain nl_11_fmt_chain;   /* Chain #9 */


/**  Forward network layer declarations  **************************************/
AI_STATIC ai_layer_nl conversion_0_layer; /* Layer #0 */
AI_STATIC ai_layer_conv2d_nl_pool conv2d_1_layer; /* Layer #1 */
AI_STATIC ai_layer_conv2d_nl_pool conv2d_3_layer; /* Layer #2 */
AI_STATIC ai_layer_conv2d_nl_pool conv2d_5_layer; /* Layer #3 */
AI_STATIC ai_layer_dense dense_8_layer; /* Layer #4 */
AI_STATIC ai_layer_dense dense_9_layer; /* Layer #5 */
AI_STATIC ai_layer_dense dense_10_layer; /* Layer #6 */
AI_STATIC ai_layer_nl dense_10_fmt_layer; /* Layer #7 */
AI_STATIC ai_layer_nl nl_11_layer; /* Layer #8 */
AI_STATIC ai_layer_nl nl_11_fmt_layer; /* Layer #9 */


/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_5_scratch1_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1536, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_5_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7168, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_scratch1_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1856, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6144, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_scratch1_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1984, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1196, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  dense_10_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 4, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  dense_10_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 512, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  dense_9_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 128, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  dense_9_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 32768, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  dense_8_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 256, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  dense_8_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 589824, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_5_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 64, AI_STATIC)

/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_5_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 18432, AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 32, AI_STATIC)

/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 4608, AI_STATIC)

/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 16, AI_STATIC)

/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 432, AI_STATIC)

/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_input_output_array, AI_ARRAY_FORMAT_U8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 12288, AI_STATIC)

/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  conversion_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 12288, AI_STATIC)

/* Array#20 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 15376, AI_STATIC)

/* Array#21 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6272, AI_STATIC)

/* Array#22 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_5_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 2304, AI_STATIC)

/* Array#23 */
AI_ARRAY_OBJ_DECLARE(
  dense_8_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 256, AI_STATIC)

/* Array#24 */
AI_ARRAY_OBJ_DECLARE(
  dense_9_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 128, AI_STATIC)

/* Array#25 */
AI_ARRAY_OBJ_DECLARE(
  dense_10_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 4, AI_STATIC)

/* Array#26 */
AI_ARRAY_OBJ_DECLARE(
  dense_10_fmt_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4, AI_STATIC)

/* Array#27 */
AI_ARRAY_OBJ_DECLARE(
  nl_11_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4, AI_STATIC)

/* Array#28 */
AI_ARRAY_OBJ_DECLARE(
  nl_11_fmt_output_array, AI_ARRAY_FORMAT_U8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 4, AI_STATIC)

/**  Array metadata declarations section  *************************************/
/* Int quant #0 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_5_scratch1_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.02264830283820629f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #1 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_scratch1_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.009164118207991123f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #2 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_scratch1_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.004234957043081522f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #3 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_10_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00011813054152298719f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #4 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_10_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.002919168211519718f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #5 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_9_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00010929624841082841f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #6 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_9_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003031205153092742f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #7 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_8_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(6.846652104286477e-05f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #8 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_8_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003023030934855342f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #9 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_5_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 64,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(1.9279337720945477e-05f, 2.0569881598930806e-05f, 1.7982983990805224e-05f, 1.9639823221950792e-05f, 1.8295973859494552e-05f, 1.9300570784253068e-05f, 1.4836224181635771e-05f, 1.5759336747578345e-05f, 1.4184454812493641e-05f, 1.6277672330033965e-05f, 2.139468961104285e-05f, 1.8479344362276606e-05f, 1.979930129891727e-05f, 2.1083444153191522e-05f, 1.835427974583581e-05f, 1.810404864954762e-05f, 1.724508183542639e-05f, 2.582481647550594e-05f, 1.799862366169691e-05f, 1.7346808817819692e-05f, 1.334869557467755e-05f, 1.689757118583657e-05f, 1.998423431359697e-05f, 2.0280262106098235e-05f, 2.4293942260555923e-05f, 1.895645800686907e-05f, 1.5068301763676573e-05f, 1.9362947568879463e-05f, 2.0879302610410377e-05f, 1.7645605112193152e-05f, 1.2624408554984257e-05f, 2.0866225895588286e-05f, 1.714529025775846e-05f, 1.71968658833066e-05f, 1.681611502135638e-05f, 2.2806687411502935e-05f, 2.0457233404158615e-05f, 2.4697183107491583e-05f, 1.3705310266232118e-05f, 1.9495337255648337e-05f, 1.941680420713965e-05f, 2.4613525965833105e-05f, 1.541293204354588e-05f, 9.937331014953088e-06f, 2.125382343365345e-05f, 2.2114089006208815e-05f, 1.940870424732566e-05f, 1.4708321941725444e-05f, 1.576862996444106e-05f, 1.6475687516503967e-05f, 1.600915493327193e-05f, 1.7786176613299176e-05f, 2.0154539015493356e-05f, 2.3614122255821712e-05f, 1.9283408619230613e-05f, 2.1087809727760032e-05f, 2.365948421356734e-05f, 2.379009674768895e-05f, 1.4093715435592458e-05f, 2.5911325792549178e-05f, 1.9689041437231936e-05f, 1.9961500584031455e-05f, 2.1023868612246588e-05f, 2.073617906717118e-05f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #10 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_5_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 64,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0021037852857261896f, 0.0022446110378950834f, 0.0019623255357146263f, 0.002143122022971511f, 0.0019964794628322124f, 0.002106102416291833f, 0.0016189472516998649f, 0.001719678402878344f, 0.001547825406305492f, 0.0017762399511411786f, 0.0023346152156591415f, 0.0020164891611784697f, 0.002160524483770132f, 0.0023006517440080643f, 0.002002841793000698f, 0.001975536346435547f, 0.0018818048993125558f, 0.002818036125972867f, 0.001964032184332609f, 0.0018929053330793977f, 0.0014566263416782022f, 0.0018438841216266155f, 0.002180704614147544f, 0.0022130075376480818f, 0.002650985261425376f, 0.0020685524214059114f, 0.0016442718915641308f, 0.00211290898732841f, 0.0022783754393458366f, 0.0019255103543400764f, 0.0013775911647826433f, 0.0022769486531615257f, 0.0018709154101088643f, 0.0018765433924272656f, 0.0018349954625591636f, 0.002488694153726101f, 0.0022323187440633774f, 0.0026949874591082335f, 0.0014955404913052917f, 0.002127355430275202f, 0.0021187858656048775f, 0.0026858586352318525f, 0.0016818783478811383f, 0.0010843739146366715f, 0.002319243736565113f, 0.0024131168611347675f, 0.0021179020404815674f, 0.0016049904515966773f, 0.0017206924967467785f, 0.0017978475661948323f, 0.00174693891312927f, 0.0019408497028052807f, 0.002199288457632065f, 0.0025768023915588856f, 0.002104229526594281f, 0.00230112811550498f, 0.002581752371042967f, 0.0025960050988942385f, 0.0015379238175228238f, 0.002827476244419813f, 0.0021484927274286747f, 0.002178223803639412f, 0.002294150646775961f, 0.0022627576254308224f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #11 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 32,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(1.5366447769338265e-05f, 1.3241236047178973e-05f, 1.3432592822937295e-05f, 1.377014814352151e-05f, 1.2055086699547246e-05f, 1.2688808055827394e-05f, 8.289704055641778e-06f, 1.2734967640426476e-05f, 1.2535587302409112e-05f, 1.1246484973526094e-05f, 1.3334202776604798e-05f, 1.3623137419926934e-05f, 8.86450015968876e-06f, 1.0125520020665135e-05f, 9.877629054244608e-06f, 9.897778909362387e-06f, 1.3512220903066918e-05f, 8.43795442051487e-06f, 1.1919920325453859e-05f, 1.4546172678819858e-05f, 7.5802549872605596e-06f, 1.2877792869403493e-05f, 1.1867158718814608e-05f, 1.0229376130155288e-05f, 8.577273547416553e-06f, 1.1314369658066425e-05f, 1.343532949249493e-05f, 1.3093125744489953e-05f, 1.194226661027642e-05f, 1.0997006029356271e-05f, 1.2132207302784082e-05f, 9.302017133450136e-06f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #12 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 32,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003628477919846773f, 0.0031266517471522093f, 0.003171836957335472f, 0.0032515437342226505f, 0.0028465664945542812f, 0.002996206982061267f, 0.0019574470352381468f, 0.003007106715813279f, 0.002960026962682605f, 0.002655631396919489f, 0.0031486039515584707f, 0.0032168300822377205f, 0.002093173563480377f, 0.002390938112512231f, 0.0023324035573750734f, 0.002337161684408784f, 0.003190639428794384f, 0.0019924533553421497f, 0.0028146496042609215f, 0.0034347863402217627f, 0.0017899249214679003f, 0.0030408320017158985f, 0.0028021910693496466f, 0.0024154616985470057f, 0.002025350695475936f, 0.002671661088243127f, 0.0031724830623716116f, 0.003091678488999605f, 0.002819926245138049f, 0.0025967219844460487f, 0.0028647768776863813f, 0.0021964844781905413f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #13 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 16,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(7.082159754645545e-06f, 7.728126547590364e-06f, 6.408522040146636e-06f, 7.544140316895209e-06f, 7.092187843227293e-06f, 7.146236384869553e-06f, 7.1763711275707465e-06f, 8.29703094495926e-06f, 7.091756287991302e-06f, 7.492049007851165e-06f, 5.833827799506253e-06f, 6.443186066462658e-06f, 6.739562650182052e-06f, 7.1669987846689764e-06f, 8.678636731929146e-06f, 7.47023432268179e-06f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #14 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 16,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0018059506546705961f, 0.0019706720486283302f, 0.001634172978810966f, 0.001923755626194179f, 0.0018085078336298466f, 0.0018222901271656156f, 0.0018299745861440897f, 0.0021157427690923214f, 0.0018083977047353983f, 0.0019104724051430821f, 0.0014876259956508875f, 0.0016430123941972852f, 0.0017185884062200785f, 0.0018275845795869827f, 0.0022130522411316633f, 0.0019049096154049039f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #15 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_input_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_U8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003921568859368563f),
    AI_PACK_UINTQ_ZP(0)))

/* Int quant #16 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conversion_0_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003921568859368563f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #17 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.004234957043081522f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #18 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.009164118207991123f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #19 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_5_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.02264830283820629f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #20 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_8_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.03605702891945839f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #21 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_9_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.040467191487550735f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #22 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_10_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.274167001247406f),
    AI_PACK_INTQ_ZP(-34)))

/* Int quant #23 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(nl_11_fmt_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_U8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00390625f),
    AI_PACK_UINTQ_ZP(0)))

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_scratch1, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 12, 2), AI_STRIDE_INIT(4, 1, 1, 64, 768),
  1, &conv2d_5_scratch1_array, &conv2d_5_scratch1_intq)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_scratch0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 7168, 1, 1), AI_STRIDE_INIT(4, 1, 1, 7168, 7168),
  1, &conv2d_5_scratch0_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_scratch1, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 29, 2), AI_STRIDE_INIT(4, 1, 1, 32, 928),
  1, &conv2d_3_scratch1_array, &conv2d_3_scratch1_intq)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_scratch0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 6144, 1, 1), AI_STRIDE_INIT(4, 1, 1, 6144, 6144),
  1, &conv2d_3_scratch0_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_scratch1, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 62, 2), AI_STRIDE_INIT(4, 1, 1, 16, 992),
  1, &conv2d_1_scratch1_array, &conv2d_1_scratch1_intq)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_scratch0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 1196, 1, 1), AI_STRIDE_INIT(4, 1, 1, 1196, 1196),
  1, &conv2d_1_scratch0_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  dense_10_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 1, 1), AI_STRIDE_INIT(4, 4, 4, 16, 16),
  1, &dense_10_bias_array, &dense_10_bias_intq)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  dense_10_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 128, 4, 1, 1), AI_STRIDE_INIT(4, 1, 128, 512, 512),
  1, &dense_10_weights_array, &dense_10_weights_intq)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  dense_9_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &dense_9_bias_array, &dense_9_bias_intq)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  dense_9_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 256, 128, 1, 1), AI_STRIDE_INIT(4, 1, 256, 32768, 32768),
  1, &dense_9_weights_array, &dense_9_weights_intq)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  dense_8_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1024, 1024),
  1, &dense_8_bias_array, &dense_8_bias_intq)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  dense_8_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 2304, 256, 1, 1), AI_STRIDE_INIT(4, 1, 2304, 589824, 589824),
  1, &dense_8_weights_array, &dense_8_weights_intq)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &conv2d_5_bias_array, &conv2d_5_bias_intq)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 3, 64), AI_STRIDE_INIT(4, 1, 32, 96, 288),
  1, &conv2d_5_weights_array, &conv2d_5_weights_intq)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_3_bias_array, &conv2d_3_bias_intq)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 16, 3, 3, 32), AI_STRIDE_INIT(4, 1, 16, 48, 144),
  1, &conv2d_3_weights_array, &conv2d_3_weights_intq)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &conv2d_1_bias_array, &conv2d_1_bias_intq)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 3, 3, 3, 16), AI_STRIDE_INIT(4, 1, 3, 9, 27),
  1, &conv2d_1_weights_array, &conv2d_1_weights_intq)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_input_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 64, 64), AI_STRIDE_INIT(4, 1, 1, 3, 192),
  1, &conv2d_input_output_array, &conv2d_input_output_intq)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  conversion_0_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 64, 64), AI_STRIDE_INIT(4, 1, 1, 3, 192),
  1, &conversion_0_output_array, &conversion_0_output_intq)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 31, 31), AI_STRIDE_INIT(4, 1, 1, 16, 496),
  1, &conv2d_1_output_array, &conv2d_1_output_intq)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 14, 14), AI_STRIDE_INIT(4, 1, 1, 32, 448),
  1, &conv2d_3_output_array, &conv2d_3_output_intq)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 6, 6), AI_STRIDE_INIT(4, 1, 1, 64, 384),
  1, &conv2d_5_output_array, &conv2d_5_output_intq)

/* Tensor #23 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_output0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 2304, 1, 1), AI_STRIDE_INIT(4, 1, 1, 2304, 2304),
  1, &conv2d_5_output_array, &conv2d_5_output_intq)

/* Tensor #24 */
AI_TENSOR_OBJ_DECLARE(
  dense_8_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 1, 1, 256, 256),
  1, &dense_8_output_array, &dense_8_output_intq)

/* Tensor #25 */
AI_TENSOR_OBJ_DECLARE(
  dense_9_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 1, 1, 128, 128),
  1, &dense_9_output_array, &dense_9_output_intq)

/* Tensor #26 */
AI_TENSOR_OBJ_DECLARE(
  dense_10_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 1, 1), AI_STRIDE_INIT(4, 1, 1, 4, 4),
  1, &dense_10_output_array, &dense_10_output_intq)

/* Tensor #27 */
AI_TENSOR_OBJ_DECLARE(
  dense_10_fmt_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 1, 1), AI_STRIDE_INIT(4, 4, 4, 16, 16),
  1, &dense_10_fmt_output_array, NULL)

/* Tensor #28 */
AI_TENSOR_OBJ_DECLARE(
  nl_11_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 1, 1), AI_STRIDE_INIT(4, 4, 4, 16, 16),
  1, &nl_11_output_array, NULL)

/* Tensor #29 */
AI_TENSOR_OBJ_DECLARE(
  nl_11_fmt_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 1, 1), AI_STRIDE_INIT(4, 1, 1, 4, 4),
  1, &nl_11_fmt_output_array, &nl_11_fmt_output_intq)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  conversion_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_input_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conversion_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conversion_0_layer, 0,
  NL_TYPE,
  nl, node_convert_integer,
  &AI_NET_OBJ_INSTANCE, &conv2d_1_layer, AI_STATIC,
  .tensors = &conversion_0_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conversion_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_1_weights, &conv2d_1_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_1_scratch0, &conv2d_1_scratch1)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_1_layer, 1,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool_integer_SSSA_ch,
  &AI_NET_OBJ_INSTANCE, &conv2d_3_layer, AI_STATIC,
  .tensors = &conv2d_1_chain, 
  .groups = 1, 
  .nl_func = NULL, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_ap_array_integer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_3_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_3_weights, &conv2d_3_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_3_scratch0, &conv2d_3_scratch1)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_3_layer, 3,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool_integer_SSSA_ch,
  &AI_NET_OBJ_INSTANCE, &conv2d_5_layer, AI_STATIC,
  .tensors = &conv2d_3_chain, 
  .groups = 1, 
  .nl_func = NULL, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_ap_array_integer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_5_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_5_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_5_weights, &conv2d_5_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_5_scratch0, &conv2d_5_scratch1)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_5_layer, 5,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool_integer_SSSA_ch,
  &AI_NET_OBJ_INSTANCE, &dense_8_layer, AI_STATIC,
  .tensors = &conv2d_5_chain, 
  .groups = 1, 
  .nl_func = NULL, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_ap_array_integer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_8_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_5_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_8_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_8_weights, &dense_8_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_8_layer, 8,
  DENSE_TYPE,
  dense, forward_dense_integer_SSSA,
  &AI_NET_OBJ_INSTANCE, &dense_9_layer, AI_STATIC,
  .tensors = &dense_8_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_9_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_8_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_9_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_9_weights, &dense_9_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_9_layer, 9,
  DENSE_TYPE,
  dense, forward_dense_integer_SSSA,
  &AI_NET_OBJ_INSTANCE, &dense_10_layer, AI_STATIC,
  .tensors = &dense_9_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_10_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_9_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_10_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_10_weights, &dense_10_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_10_layer, 10,
  DENSE_TYPE,
  dense, forward_dense_integer_SSSA,
  &AI_NET_OBJ_INSTANCE, &dense_10_fmt_layer, AI_STATIC,
  .tensors = &dense_10_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_10_fmt_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_10_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_10_fmt_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_10_fmt_layer, 10,
  NL_TYPE,
  nl, node_convert,
  &AI_NET_OBJ_INSTANCE, &nl_11_layer, AI_STATIC,
  .tensors = &dense_10_fmt_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_11_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_10_fmt_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_11_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_11_layer, 11,
  NL_TYPE,
  nl, forward_sm,
  &AI_NET_OBJ_INSTANCE, &nl_11_fmt_layer, AI_STATIC,
  .tensors = &nl_11_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_11_fmt_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_11_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_11_fmt_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_11_fmt_layer, 11,
  NL_TYPE,
  nl, node_convert,
  &AI_NET_OBJ_INSTANCE, &nl_11_fmt_layer, AI_STATIC,
  .tensors = &nl_11_fmt_chain, 
)


AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 648576, 1,
                     NULL),
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 23856, 1,
                     NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &conv2d_input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &nl_11_fmt_output),
  &conversion_0_layer, 0, NULL)



AI_DECLARE_STATIC
ai_bool network_configure_activations(
  ai_network* net_ctx, const ai_buffer* activation_buffer)
{
  AI_ASSERT(net_ctx &&  activation_buffer && activation_buffer->data)

  ai_ptr activations = AI_PTR(AI_PTR_ALIGN(activation_buffer->data, AI_NETWORK_ACTIVATIONS_ALIGNMENT));
  AI_ASSERT(activations)
  AI_UNUSED(net_ctx)

  {
    /* Updating activations (byte) offsets */
    conv2d_5_scratch1_array.data = AI_PTR(activations + 13440);
    conv2d_5_scratch1_array.data_start = AI_PTR(activations + 13440);
    conv2d_5_scratch0_array.data = AI_PTR(activations + 6272);
    conv2d_5_scratch0_array.data_start = AI_PTR(activations + 6272);
    conv2d_3_scratch1_array.data = AI_PTR(activations + 22000);
    conv2d_3_scratch1_array.data_start = AI_PTR(activations + 22000);
    conv2d_3_scratch0_array.data = AI_PTR(activations + 15856);
    conv2d_3_scratch0_array.data_start = AI_PTR(activations + 15856);
    conv2d_1_scratch1_array.data = AI_PTR(activations + 17564);
    conv2d_1_scratch1_array.data_start = AI_PTR(activations + 17564);
    conv2d_1_scratch0_array.data = AI_PTR(activations + 16368);
    conv2d_1_scratch0_array.data_start = AI_PTR(activations + 16368);
    conv2d_input_output_array.data = AI_PTR(NULL);
    conv2d_input_output_array.data_start = AI_PTR(NULL);
    conversion_0_output_array.data = AI_PTR(activations + 4080);
    conversion_0_output_array.data_start = AI_PTR(activations + 4080);
    conv2d_1_output_array.data = AI_PTR(activations + 480);
    conv2d_1_output_array.data_start = AI_PTR(activations + 480);
    conv2d_3_output_array.data = AI_PTR(activations + 0);
    conv2d_3_output_array.data_start = AI_PTR(activations + 0);
    conv2d_5_output_array.data = AI_PTR(activations + 14976);
    conv2d_5_output_array.data_start = AI_PTR(activations + 14976);
    dense_8_output_array.data = AI_PTR(activations + 0);
    dense_8_output_array.data_start = AI_PTR(activations + 0);
    dense_9_output_array.data = AI_PTR(activations + 256);
    dense_9_output_array.data_start = AI_PTR(activations + 256);
    dense_10_output_array.data = AI_PTR(activations + 0);
    dense_10_output_array.data_start = AI_PTR(activations + 0);
    dense_10_fmt_output_array.data = AI_PTR(activations + 4);
    dense_10_fmt_output_array.data_start = AI_PTR(activations + 4);
    nl_11_output_array.data = AI_PTR(activations + 20);
    nl_11_output_array.data_start = AI_PTR(activations + 20);
    nl_11_fmt_output_array.data = AI_PTR(NULL);
    nl_11_fmt_output_array.data_start = AI_PTR(NULL);
    
  }
  return true;
}



AI_DECLARE_STATIC
ai_bool network_configure_weights(
  ai_network* net_ctx, const ai_buffer* weights_buffer)
{
  AI_ASSERT(net_ctx &&  weights_buffer && weights_buffer->data)

  ai_ptr weights = AI_PTR(weights_buffer->data);
  AI_ASSERT(weights)
  AI_UNUSED(net_ctx)

  {
    /* Updating weights (byte) offsets */
    
    dense_10_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_10_bias_array.data = AI_PTR(weights + 648560);
    dense_10_bias_array.data_start = AI_PTR(weights + 648560);
    dense_10_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_10_weights_array.data = AI_PTR(weights + 648048);
    dense_10_weights_array.data_start = AI_PTR(weights + 648048);
    dense_9_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_9_bias_array.data = AI_PTR(weights + 647536);
    dense_9_bias_array.data_start = AI_PTR(weights + 647536);
    dense_9_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_9_weights_array.data = AI_PTR(weights + 614768);
    dense_9_weights_array.data_start = AI_PTR(weights + 614768);
    dense_8_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_8_bias_array.data = AI_PTR(weights + 613744);
    dense_8_bias_array.data_start = AI_PTR(weights + 613744);
    dense_8_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_8_weights_array.data = AI_PTR(weights + 23920);
    dense_8_weights_array.data_start = AI_PTR(weights + 23920);
    conv2d_5_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_5_bias_array.data = AI_PTR(weights + 23664);
    conv2d_5_bias_array.data_start = AI_PTR(weights + 23664);
    conv2d_5_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_5_weights_array.data = AI_PTR(weights + 5232);
    conv2d_5_weights_array.data_start = AI_PTR(weights + 5232);
    conv2d_3_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_3_bias_array.data = AI_PTR(weights + 5104);
    conv2d_3_bias_array.data_start = AI_PTR(weights + 5104);
    conv2d_3_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_3_weights_array.data = AI_PTR(weights + 496);
    conv2d_3_weights_array.data_start = AI_PTR(weights + 496);
    conv2d_1_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_bias_array.data = AI_PTR(weights + 432);
    conv2d_1_bias_array.data_start = AI_PTR(weights + 432);
    conv2d_1_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_weights_array.data = AI_PTR(weights + 0);
    conv2d_1_weights_array.data_start = AI_PTR(weights + 0);
  }

  return true;
}


/**  PUBLIC APIs SECTION  *****************************************************/

AI_API_ENTRY
ai_bool ai_network_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if ( report && net_ctx )
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = {AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR,
                            AI_TOOLS_API_VERSION_MICRO, 0x0},

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 8933820,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .activations       = AI_STRUCT_INIT,
      .params            = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if ( !ai_platform_api_get_network_report(network, &r) ) return false;

    *report = r;
    return true;
  }

  return false;
}

AI_API_ENTRY
ai_error ai_network_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_network_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_handle ai_network_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_network_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if ( !net_ctx ) return false;

  ai_bool ok = true;
  ok &= network_configure_weights(net_ctx, &params->params);
  ok &= network_configure_activations(net_ctx, &params->activations);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_network_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_network_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}




#undef AI_NETWORK_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME


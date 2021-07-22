/*
 * @Author: lebhoryi@gmail.com
 * @Date: 2021-06-30 16:52:58
 * @LastEditors: lebhoryi@gmail.com
 * @LastEditTime: 2021-07-01 19:36:20
 * @Version: V0.0.1
 * @FilePath: /art_pi/applications/fire_detection.c
 * @Description: fire detection demo app
 */
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"
#include <rtdevice.h>
#include "drv_spi_ili9488.h"  // spi lcd driver
#include <lcd_spi_port.h>  // lcd ports

/* fire detection */
#include <rt_ai_network_model.h>
#include <rt_ai.h>
#include <rt_ai_log.h>
#include <backend_cubeai.h>
#include <logo.h>
#include<test.h>
/* ������ƿ� */
static struct rt_mailbox mb;
/* ���ڷ��ʼ����ڴ�� */
static char mb_pool[128];
float *input_buf;
char *gesture_label[] = {"fist","gun","Iloveyou","thumbUp"};
struct rt_event ov2640_event;
rt_ai_buffer_t ai_flag = 0;
extern int rt_gc0328c_init(void);
extern void DCMI_Start(void);
static inline void _itof(float *dst,rt_uint8_t *src, uint32_t size, float div);


void ai_run_complete(void *arg){
    *(int*)arg = 1;
}

void ai_camera();
void bilinera_interpolation(rt_uint8_t *in_array, short height, short width,
                            rt_uint8_t *out_array, short out_height, short out_width);


rt_thread_t tcpclient_thread = RT_NULL;


void tcpclient_real_thread(void *para)
{
    extern void tcpclient(void);
    tcpclient();
}
int hands_app(void){
    //rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

    struct drv_lcd_device *lcd;
    struct rt_device_rect_info rect_info = {0, 0, LCD_WIDTH, 240};
    lcd = (struct drv_lcd_device *)rt_device_find("lcd");

//    lcd_show_image(0, 0, 320, 240, LOGO);
//    lcd_show_string(90, 140, 16, "Hello Hands!");
//    lcd_show_string(90, 156, 16, "Demo: Gesture Recognition");
//    rt_thread_mdelay(1000);
    if (sizeof(TEST)<(320*240*3)){
        rt_kprintf("err %d",sizeof(TEST));
        return -1;
    }
    lcd_show_image(0, 0, 320, 240, TEST);
    input_buf = rt_malloc(64*64*sizeof(float));
    //
    // lcd_show_string(90, 140, 16, "Hello RT-Thread!");
    // lcd_show_string(90, 156, 16, "Demo: Gesture Recognition");
    /* init spi data notify event */
    rt_event_init(&ov2640_event, "ov2640", RT_IPC_FLAG_FIFO);
    rt_mb_init(&mb,
                       "mbt",                      /* ������ mbt */
                       &mb_pool[0],                /* �����õ����ڴ���� mb_pool */
                       sizeof(mb_pool) / 4,        /* �����е��ʼ���Ŀ����Ϊһ���ʼ�ռ 4 �ֽ� */
                       RT_IPC_FLAG_FIFO);          /* ���� FIFO ��ʽ�����̵߳ȴ� */




    rt_err_t result = RT_EOK;


    /* find a registered model handle */
    static rt_ai_t model = NULL;
    //
    //rt_ai_t model = NULL;
    model = rt_ai_find(RT_AI_NETWORK_MODEL_NAME);
    /////////////////////////////////
    if(!model) {rt_kprintf("ai model find err\r\n"); return -1;}


#if 1
    /* init the model and allocate memory */
    rt_ai_buffer_t *work_buffer = rt_malloc(RT_AI_NETWORK_WORK_BUFFER_BYTES);

    result = rt_ai_init(model, work_buffer);
    if (result != 0) {rt_kprintf("ai model init err\r\n"); return -1;}

    /* prepare input data */
    rt_ai_buffer_t *input_image = rt_malloc(RT_AI_NETWORK_IN_1_SIZE_BYTES);
    if (!input_image) {rt_kprintf("malloc input memory err\n"); return -1;}
    // allocate output memory
    rt_ai_buffer_t *_out = rt_malloc(RT_AI_NETWORK_OUT_1_SIZE_BYTES);
    if (!_out) {rt_kprintf("malloc err\n"); return -1;}
    rt_ai_config(model, CFG_INPUT_0_ADDR, input_image);
    rt_ai_config(model, CFG_OUTPUT_0_ADDR,_out);
    ai_camera();

    tcpclient_thread = rt_thread_create("tcpclient", tcpclient_real_thread, RT_NULL, 2048, 15, 10);
    rt_thread_startup(tcpclient_thread);
    rt_kprintf("tcpclient startup success.\n");
        while(1)
        {
            //rt_pin_write(LED_PIN, PIN_LOW);
//            rt_kprintf("%d\n",__LINE__);
            rt_event_recv(&ov2640_event,
                                1,
                                RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
                                RT_WAITING_FOREVER,
                                RT_NULL);
//            rt_kprintf("%d\n",__LINE__);
            //rt_pin_write(LED_PIN, PIN_HIGH);
            lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, &rect_info);
            if (ai_flag > 0)
            {
                // resize
                bilinera_interpolation(lcd->lcd_info.framebuffer, 240, 320, input_image, 64, 64);
                rt_ai_run(model, NULL, NULL);
                uint8_t *out = (uint8_t *)rt_ai_output(model, 0);
//                rt_kprintf("pred: %d %d %d %d\n", out[0], out[1],out[2],out[3]);
                  if (out[0] > 200){
                  rt_mb_send(&mb, (rt_uint32_t)&gesture_label[0][0]);
                  lcd_show_string(20, 20, 16, "Fist");}
                  if(out[1] > 200){rt_mb_send(&mb, (rt_uint32_t)&gesture_label[1][0]);
                  lcd_show_string(20, 20, 16, "Gun");}
                  if (out[2] > 200){rt_mb_send(&mb, (rt_uint32_t)&gesture_label[2][0]);
                  lcd_show_string(20, 20, 16, "Iloveyou");}
                  if (out[3] > 200){rt_mb_send(&mb, (rt_uint32_t)&gesture_label[3][0]);
                  lcd_show_string(20, 20, 16, "ThumbUp");}
            }
//            rt_kprintf("%d\n",__LINE__);
            DCMI_Start();
        }
        rt_free(input_image);
        rt_free(work_buffer);
        rt_free(_out);

        return 0;

//    // resize
//    bilinera_interpolation((rt_uint8_t *)TEST, 240, 320, input_image, 64, 64);
//
//    //
//    rt_memcpy(model->input[0], input_image, RT_AI_NETWORK_IN_1_SIZE_BYTES);
////    _itof(input_buf,input_image, 64*64, 255.0);
//  /////////////////////////////////
//
//    /* run ai model */
//    result = rt_ai_run(model, ai_run_complete, &ai_run_complete_flag);
//    if (result != 0) {rt_kprintf("ai model run err\r\n"); return -1;}
//
//    /* get output and post-process the output */
// //   uint8_t *pred;
//    int max_index = 0;
//    if(ai_run_complete_flag){
//        //
//   //get inferance data
//        uint8_t *out = (uint8_t *)rt_ai_output(model, 0);
//        //get argmax
//        for(int i = 1 ; i < 4; i++){
//            if(out[i] > out[max_index]){
//                max_index = i;
//            }
//        }
//        AI_LOG("The gesture prediction is : %s\n", gesture_label[max_index]);
//      /////////////////////////////////
//         rt_kprintf("pred: %d %d %d %d\n", out[0], out[1],out[2],out[3]);
////         if (out[0] > 200)
////         lcd_show_string(20, 20, 16, "Fire");
////         else
////         lcd_show_string(20, 20, 16, "No Fire");
//    }
//    rt_free(work_buffer);
#endif



return 0;
}
MSH_CMD_EXPORT(hands_app,hands demo);
//INIT_APP_EXPORT(hands_app);

static inline void _itof(float *dst,rt_uint8_t *src, uint32_t size, float div){
    if (div == 0){
        return ;
    }else{
        int i = 0;
        for(i = 0; i < size; i++){
            dst[i] = (float)src[i] / div;
        }
    }
}

int is_in_array(short x, short y, short height, short width)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
        return 1;
    else
        return 0;
}


void bilinera_interpolation(rt_uint8_t* in_array, short height, short width,
                            rt_uint8_t* out_array, short out_height, short out_width)
{
    double h_times = (double)out_height / (double)height,
           w_times = (double)out_width / (double)width;
    short  x1, y1, x2, y2, f11, f12, f21, f22;
    double x, y;

    for (int i = 0; i < out_height; i++){
        for (int j = 0; j < out_width*3; j=j+3){
            for (int k =0; k <3; k++){
                x = j / w_times + k;
                y = i / h_times;

                x1 = (short)(x - 3);
                x2 = (short)(x + 3);
                y1 = (short)(y + 1);
                y2 = (short)(y - 1);
                f11 = is_in_array(x1, y1, height, width*3) ? in_array[y1*width*3+x1] : 0;
                f12 = is_in_array(x1, y2, height, width*3) ? in_array[y2*width*3+x1] : 0;
                f21 = is_in_array(x2, y1, height, width*3) ? in_array[y1*width*3+x2] : 0;
                f22 = is_in_array(x2, y2, height, width*3) ? in_array[y2*width*3+x2] : 0;
                out_array[i*out_width*3+j+k] = (rt_uint8_t)(((f11 * (x2 - x) * (y2 - y)) +
                                           (f21 * (x - x1) * (y2 - y)) +
                                           (f12 * (x2 - x) * (y - y1)) +
                                           (f22 * (x - x1) * (y - y1))) / ((x2 - x1) * (y2 - y1)));
            }
        }
    }
}
void ai_camera()
{
    rt_gc0328c_init();
    ai_flag = 1;
    DCMI_Start();
}

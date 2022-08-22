
#include <stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/queue.h>


TaskHandle_t task1_handle,task2_handle,task3_handle,task4_handle,task5_handle;
QueueHandle_t mq_data;


void task_1(void *data)
{
    UBaseType_t priority;
    priority = uxTaskPriorityGet(task_1);
   while(1)
   {
        printf("Task_1: Starting Task 1 With Priority:%d\n",priority);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
     vTaskDelete(task1_handle);
}

void task_2(void *data)
{
    UBaseType_t priority;
    priority = uxTaskPriorityGet(task_2);
   while(1)
   {
        printf("Task_2: Starting Task 2 With Priority:%d\n",priority);
        vTaskDelay(2000/portTICK_PERIOD_MS);
    }
    vTaskDelete(task2_handle);
}

void task_3(void *data)
{
    UBaseType_t priority;
    priority = uxTaskPriorityGet(task_3);
   while(1)
   {
        printf("Task_3: Starting Task 3 With Priority:%d\n",priority);
        vTaskDelay(5000/portTICK_PERIOD_MS);
    }
    vTaskDelete(task3_handle);
}


void task_4(void *data)
{
    UBaseType_t priority;
    priority = uxTaskPriorityGet(task_4);
    printf("Task_4: Starting Task 4 With Priority:%d\n",priority);
    int send_data=0;
    while(1)
    {
        send_data++;
       printf("Task_4:Sending Data: %d\n",send_data);
       xQueueSend(mq_data,&send_data,portMAX_DELAY);
       vTaskDelay(1000/portTICK_PERIOD_MS);
        
      }
      vTaskDelete(task4_handle);
}

void task_5(void *data)
{
    UBaseType_t priority;
    priority = uxTaskPriorityGet(task_5);
    printf("Task_5: Starting Task 5 With Priority:%d\n",priority);
    int recv_data=0;
    while(1)
    {
        xQueueReceive(mq_data,&recv_data,portMAX_DELAY);
        printf("Task_5:Received Data: %d\n",recv_data);
    }
    vTaskDelete(task5_handle);
}
       

void app_main()
{
    BaseType_t res;
    UBaseType_t priority;
    priority = uxTaskPriorityGet(NULL);
    printf("Main Task: Main Task Started...With Prioty:%d\n",priority);
    //creating queue
    mq_data=xQueueCreate(10,sizeof(int));
    //creating task
    res = xTaskCreate(task_1,"task_1",2048,NULL,5,&task1_handle);
    res = xTaskCreate(task_2,"task_2",2048,NULL,6,&task2_handle);
    res = xTaskCreate(task_3,"task_3",2048,NULL,7,&task3_handle);
    res = xTaskCreate(task_4,"task_4",2048,NULL,8,&task4_handle);
    res = xTaskCreate(task_5,"task_5",2048,NULL,9,&task5_handle);
    if( res == pdPASS)
    {
        printf("Main Task: Tasks Created Successfully\n");
    }
}


#include <stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/timers.h>

TaskHandle_t task1_handle,task2_handle,task3_handle;
TimerHandle_t timer_handle;

void timer_callback(TimerHandle_t xTimer)
{
    printf("Timer Fired\n");
}


void task_1(void *data)
{
   UBaseType_t priority;
   priority = uxTaskPriorityGet(task_1);
  while(1)
  {
      printf("Task_1: Starting Task1 Started With Priority:%d\n",priority);
      vTaskDelay(1000/portTICK_PERIOD_MS);
   }
}

void task_2(void *data)
{
   UBaseType_t priority;
   priority = uxTaskPriorityGet(task_2);
  while(1)
  {
      printf("Task_2:Starting Task2 Started With Priority:%d\n",priority);
      vTaskDelay(2000/portTICK_PERIOD_MS);
   }
}

void task_3(void *data)
{
   UBaseType_t priority;
   priority = uxTaskPriorityGet(task_3);
  while(1)
  {
      printf("Task_3: Starting Task3 With Priority: %d\n",priority);
      vTaskDelay(5000/portTICK_PERIOD_MS);
      printf("Creating The Timer\n");
      timer_handle = xTimerCreate("OneShotTimer",10000/portTICK_PERIOD_MS,pdFALSE,0,timer_callback);
      printf("Starting The Timer\n");
      xTimerStart(timer_handle,0);
   }
   vTaskDelete(task3_handle);
}

void app_main()
{
   BaseType_t res;
   UBaseType_t priority;
   priority = uxTaskPriorityGet(NULL);
   printf("Main Task Started...with Priority:%d\n",priority);

    //creating task
    res = xTaskCreate(task_1,"task_1",2048,NULL,5,&task1_handle);
    res = xTaskCreate(task_2,"task_1",2048,NULL,6,&task2_handle);
    res = xTaskCreate(task_3,"task_1",2048,NULL,7,&task3_handle);
    if (res == pdPASS)
       {
          printf("Task Created Succesfully..\n");
       }
}

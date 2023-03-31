/* Edge Impulse ingestion SDK
 * Copyright (c) 2022 EdgeImpulse Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/* Includes ---------------------------------------------------------------- */
#include <Colour_Classifications_inferencing.h>


#define BUFFER_BARIS 12
#define JUMLAH_KOLOM 3

String buffer_string;  // untuk menyimpan data input serial
char *strings_dataInput[JUMLAH_KOLOM];
char *ptr = NULL;
float RED;
float GREEN;
float BLUE;


/*
static const float features[] = {
    // copy raw features here (for example from the 'Live classification' page)
    // see https://docs.edgeimpulse.com/docs/running-your-impulse-arduino
    69, 109, 9
};
*/

// inisialisasi
float features[] = {    
    0, 0, 0
};

/**
 * @brief      Copy raw feature data in out_ptr
 *             Function called by inference library
 *
 * @param[in]  offset   The offset
 * @param[in]  length   The length
 * @param      out_ptr  The out pointer
 *
 * @return     0
 */
int raw_feature_get_data(size_t offset, size_t length, float *out_ptr) {
    memcpy(out_ptr, features + offset, length * sizeof(float));
    return 0;
}

void print_inference_result(ei_impulse_result_t result);

/**
 * @brief      Arduino setup function
 */
void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    // comment out the below line to cancel the wait for USB connection (needed for native USB)
    while (!Serial);
    Serial.println("Masukkan Nilai RGB, pisahkan dengan koma");
}

/**
 * @brief      Arduino main function
 */
void loop()
{
    if(Serial.available()){
      buffer_string = Serial.readStringUntil('\n');
      //Ubah String ke array char untuk tiap data 
      char charBuf[BUFFER_BARIS];
      buffer_string.toCharArray(charBuf, BUFFER_BARIS);

      //pecah string sesuai delimiter (kita pakai koma)
      byte index = 0;
      ptr = strtok(charBuf, ","); //delimiter koma
      while (ptr != NULL){
        strings_dataInput[index] = ptr;
        index++;
        ptr = strtok(NULL, ",");
      }

      RED = atof(strings_dataInput[0]); //float
      GREEN = atof(strings_dataInput[1]);
      BLUE = atof(strings_dataInput[2]);

      // ini feature yang akan diberikan ke classifier
      features[0] = RED;
      features[1] = GREEN;
      features[2] = BLUE; 

      ei_printf("Edge Impulse standalone inferencing (Arduino)\n");

      if (sizeof(features) / sizeof(float) != EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE) {
          ei_printf("The size of your 'features' array is not correct. Expected %lu items, but had %lu\n",
              EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, sizeof(features) / sizeof(float));
          delay(1000);
          return;
      }

      ei_impulse_result_t result = { 0 };

      // the features are stored into flash, and we don't want to load everything into RAM
      signal_t features_signal;
      features_signal.total_length = sizeof(features) / sizeof(features[0]);
      features_signal.get_data = &raw_feature_get_data;

      // invoke the impulse
      EI_IMPULSE_ERROR res = run_classifier(&features_signal, &result, false /* debug */);
      if (res != EI_IMPULSE_OK) {
          ei_printf("ERR: Failed to run classifier (%d)\n", res);
          return;
      }

      // print inference return code
      ei_printf("run_classifier returned: %d\r\n", res);
      print_inference_result(result);
  
      //delay(1000);
  }    
}

void print_inference_result(ei_impulse_result_t result) {

    // Print how long it took to perform inference
    ei_printf("Timing: DSP %d ms, inference %d ms, anomaly %d ms\r\n",
            result.timing.dsp,
            result.timing.classification,
            result.timing.anomaly);

    // Print the prediction results (object detection)
#if EI_CLASSIFIER_OBJECT_DETECTION == 1
    ei_printf("Object detection bounding boxes:\r\n");
    for (uint32_t i = 0; i < result.bounding_boxes_count; i++) {
        ei_impulse_result_bounding_box_t bb = result.bounding_boxes[i];
        if (bb.value == 0) {
            continue;
        }
        ei_printf("  %s (%f) [ x: %u, y: %u, width: %u, height: %u ]\r\n",
                bb.label,
                bb.value,
                bb.x,
                bb.y,
                bb.width,
                bb.height);
    }

    // Print the prediction results (classification)
#else
    ei_printf("Predictions:\r\n");
    for (uint16_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
        ei_printf("  %s: ", ei_classifier_inferencing_categories[i]);
        ei_printf("%.5f\r\n", result.classification[i].value);
    }
#endif

    // Print anomaly result (if it exists)
#if EI_CLASSIFIER_HAS_ANOMALY == 1
    ei_printf("Anomaly prediction: %.3f\r\n", result.anomaly);
#endif

}
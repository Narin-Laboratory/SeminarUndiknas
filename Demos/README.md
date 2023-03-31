### Terdapat dua demo dalam folder ini:
#### 1. Klasifikasi buah menggunakan KNN pada Arduino
Demo ini menggunakan papan mikrokontroler Raspberry Pi Pico. Tempatkan sebuah pushbutton pada GP21 dan GND, tanpa perlu menambahkan resistor. Kita akan mengaktifkan mode input pull-up dalam program.
Pasang sensor warna ke mikrokontroler. Saat ini saya menggunakan TCS34725. Hubungkan pin SDA sensor ke GP4, dan pin SCL sensor ke GP5 pada Pico. Hubungkan pin 3V3 sensor dengan 3V3 (OUT) pada pico. Terakhir, hubungkan GND sensor dengan GND Pico.

Setelah komponen terpasang, unggah program <b>Fruits_classification_using_color_sensor_COLLECT_DATA.ino</b> ke Pico. Siapkan beberapa jenis buah yang berbeda (kalau bisa, memiliki perbedaan setiap buah memiliki perbedaan warna yang mencolok). Saat ini saya menggunakan 3 jenis buah, yaitu Apel, Lemon, dan Alpukat. Anda bisa mengganti dengan jenis yang lain. Editlah jumlah class dalam program sesuai dengan jumlah buah yang ingin diklasifikasikan.
Tekan pushbutton setiap ingin mengambil sampel untuk masing-masing buah. Hasil pengukuran warna akan terlihat dalam Serial Monitor. Setelah selesai mengambil data, copy-paste ke <b>Fruits_classification_using_color_sensor_INFERENCE.ino</b>.

Untuk klasiifikasi, unggahlah file <b>Fruits_classification_using_color_sensor_INFERENCE.ino</b>. Dalam file <b>Fruits_classification_using_color_sensor_INFERENCE.ino</b>, saya telah menyertakan hasil pengambilan data dari sensor saya. Anda bisa mengubahnya sesuai dengan hasil pengukuran dari sensor Anda sendiri.

#### 2. Motion recognition menggunakan edge impulse
Dalam demo ini, saya menggunakan papan Arduino BLE SENSE. Lihat spesifikasinya disini (https://docs.arduino.cc/hardware/nano-33-ble-sense). Papan ini telah disertai dengan sensor accelerometer. Untuk tutorial, bisa dipelajari di sini (https://docs.edgeimpulse.com/docs/tutorials/continuous-motion-recognition).
Pertama, ambilah data secara live. Koneksikan papan sesuai dengan tutorial berikut:
https://docs.edgeimpulse.com/docs/development-platforms/officially-supported-mcu-targets/arduino-nano-33-ble-sense
dan ambilah beberapa gerakan tangan yang berbeda. Saya menggunakan 4 jenis gerakan tangan yang berbeda: Diam, Kanan-kiri, Atas-bawah, Lambai. Lihat video presentasi untuk lebih jelasnya.
Selanjutnya, training model, dan terakhir unggah file ke papan mikrokontroler.
Dalam repositori ini, saya sertakan file yang siap di unggah ke Pico. 





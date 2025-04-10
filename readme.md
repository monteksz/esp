# Proyek ESP32 Menggunakan Modul ESPNOW

<div align="justify">

Proyek ini memanfaatkan modul ESP32 dengan fitur ESP-NOW untuk membangun sistem komunikasi nirkabel yang cepat, ringan, dan hemat daya antar perangkat. Dengan teknologi ESP-NOW, ESP32 dapat saling bertukar data secara langsung, menjadikannya solusi ideal untuk aplikasi seperti sensor jaringan, pengendali jarak jauh, dan sistem monitoring terdistribusi.

</div>

## Alat Yang Digunakan
1. ESP32  
2. ESP32 Cam  
3. PIR Sensor  
4. Kabel USB  

## Goal

<div align="justify">

Tujuan dari proyek ini adalah membangun sebuah sistem berbasis ESP32 yang mampu mendeteksi pergerakan menggunakan sensor PIR, kemudian secara otomatis mengambil foto dan mengirimkannya ke perangkat ESP32 server melalui protokol ESP-NOW. Sistem ini menggunakan satu ESP32 sebagai unit pengirim (sender) yang terhubung dengan kamera dan sensor PIR, dan satu ESP32 lainnya sebagai server yang berfungsi menerima data gambar dari sender. Setelah gambar diterima, ESP32 server akan langsung meneruskannya ke akun Telegram pengguna sebagai notifikasi real-time. Dengan konsep ini, proyek bertujuan menciptakan sistem keamanan ringkas, efisien, dan hemat daya, namun tetap mampu memberi peringatan sederhana melalui Telegram.

</div>

## Update Log - 24 Maret 2025 (v0.0.1-Beta)
<div align="justify">

Pada versi awal proyek ini (v0.0.1-Beta), ESP32 sender telah berhasil mengirimkan pesan sederhana berupa teks menggunakan modul ESP-NOW. Sementara itu, ESP32 yang berperan sebagai server juga sudah mampu menerima pesan tersebut dengan baik. Pengujian awal menunjukkan komunikasi antar perangkat ESP32 berjalan lancar untuk data ringan. Namun, pada tahap ini, pengiriman data dari server ke Telegram masih belum berhasil, sehingga proses notifikasi ke pengguna belum dapat dilakukan. Kendala ini menjadi fokus utama untuk pengembangan versi selanjutnya, terutama dalam integrasi ESP32 dengan API Telegram secara stabil.

</div>

## Bug Report - 24 Maret 2025 (v0.0.1-Beta)
<div align="justify">

Pada tahap awal versi v0.0.1-Beta, ESP32 sender sudah berhasil mengirimkan pesan teks sederhana menggunakan protokol ESP-NOW, dan ESP32 server telah berhasil menerimanya. Namun, saat server mencoba meneruskan pesan tersebut ke akun Telegram pengguna menggunakan Bot API, ESP server gagal meneruskan pesan dari sender ke telegram.

### Log Error Pengunaan
1. Jalankan ESP32 sender dan server.
2. Sender mengirimkan pesan teks melalui ESP-NOW.
3. Server menerima pesan.
4. Server mencoba mengirim pesan tersebut ke Telegram.
5. Server gagal meneruskan atau mengirim pesan dari sender ke Telegram.

### Keadaan Yang Diharapkan
Setelah pesan teks diterima oleh server, server seharusnya mengirimkannya ke akun Telegram yang dituju menggunakan Bot API.
### Keadaan Saat Ini
Pesan dari sender berhasil diterima oleh server tapi server tidak bisa meneruskan pesan tersebut ke Telegram.
</div>

### Kemungkinan Penyebab

<div align="center">

<table>
  <thead>
    <tr>
      <th>Kemungkinan Penyebab</th>
      <th>Status</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>⚠️ Token Bot Telegram belum valid atau salah</td>
      <td>❌ Tidak Mungkin — Sebelum memakai modul ESPNOW, Server bisa saling berkomunikasi dengan telegram</td>
    </tr>
    <tr>
      <td>⚠️ Koneksi internet pada ESP32 server tidak aktif atau tidak stabil</td>
      <td>✔️ Sangat Mungkin — Koneksi WIFI pada ESP32 Server tidak stabil atau tidak terhubung</td>
    </tr>
    <tr>
      <td>⚠️ Format URL atau payload Telegram API tidak sesuai</td>
      <td>⚖️ 50:50 — Implementasi API Telegram yang mungkin kurang tepat atau salah</td>
    </tr>
    <tr>
      <td>❌ ESP32 server belum menerima pesan dari sender</td>
      <td>❌ Tidak Mungkin — ESP32 Server sudah menerima pesan sederhana dari sender</td>
    </tr>
  </tbody>
</table>

</div>

## Final Log
Pondasi awal untuk v0.0.1 tidak sepenuhnya berhasil akan tetapi akan di update secepatnya agar proyek ini dapat berjalan dengan semestinya.

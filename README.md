# Tugas UTS Lab Grafika Komputer

## Anggota
- **Hotbaen Eliezer Situmorang** (221401070)
- **Brian Abednego Beltsazar Silitonga** (221401088)
- **Ferry Fernandoli Sirait** (221401097)

## Deskripsi Proyek
Proyek ini menggunakan library **OpenGL** dan **FreeGLUT** untuk memungkinkan pengguna menggambar, menggerakkan, dan membuat animasi sederhana pada karakter **Mario**, salah satu karakter video game populer. Dalam proyek ini, Mario dapat berjalan ke kiri dan kanan serta melakukan lompatan sederhana. Lingkungan sekitar seperti awan, gunung, dan balok bergerak dengan efek parallax untuk memberikan kesan kedalaman.

## Cara Menjalankan Karakter
- **Arah Kiri ('a')**: Mario akan berjalan ke kiri. Jika Mario berada di tepi layar, lingkungan (awan, gunung, dan latar) akan bergerak ke arah kanan untuk memberikan efek perpindahan latar. Mario tidak akan bergerak lebih jauh jika sudah mencapai ujung dari sisi kiri.
- **Arah Kanan ('d')**: Mario akan berjalan ke kanan. Jika Mario mencapai tengah, lingkungan akan bergeser ke arah kiri, memberi kesan Mario terus berjalan.
- **Lompat ('spasi')**: Mario dapat melompat jika saat ini tidak berada dalam posisi melompat.

## Struktur Utama Kode
### Fungsi Utama
- **drawPixel**: Menggambar satu pixel berwarna di posisi tertentu.
- **drawMario**: Menggambar karakter Mario dalam bentuk piksel berwarna pada matriks 16x16 menggunakan `drawPixel`.
- **drawCloud, drawCloudsWithParallax**: Menggambar awan pada layar dengan efek parallax menggunakan dua lapisan awan bergerak.
- **drawBrick, setBrickSize**: Menggambar balok dengan pola, menggunakan warna khusus dan pengaturan ukuran.
- **updateJump**: Mengatur pergerakan lompatan Mario, menambah efek gravitasi hingga Mario kembali ke tanah.
- **keyboard**: Fungsi input keyboard untuk mengatur kontrol gerakan Mario: `a` untuk ke kiri, `d` untuk ke kanan, dan `spasi` untuk lompat.
- **drawMountain, drawMountainsWithParallax**: Menggambar gunung di latar belakang dengan ukuran dan warna yang diatur menggunakan efek parallax.
- **display**: Fungsi utama yang memanggil seluruh elemen gambar (Mario, awan, gunung, dan balok) serta mengatur pergerakan lompatan Mario dan perpindahan parallax pada latar belakang.

## Kredit
- **OpenGL**: Open Graphics Library, digunakan untuk rendering grafik 2D dan 3D.
- **FreeGLUT**: Free OpenGL Utility Toolkit, digunakan untuk manajemen jendela dan input di OpenGL.
- **Karakter Mario**: Dimiliki oleh Nintendo. Implementasi ini hanya untuk keperluan edukasi dalam proyek grafika komputer.

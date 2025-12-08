<h1 align="center">Collision Simulator</h1>

<center>Project collision simulator ini dibuat untuk Final Project dari mata kuliah Struktur Data dan Analisis Algoritma. Dosen pengampu yaitu Bapak Arta Kusuma Hernanda. Collision simulator ini menggunakan basic Brute Force algorithm sebagai salah satu landasan untuk logika collision. Tak hanya itu, Raylib menjadi sebuah framework utama untuk membuat object dari bola, window size, dan text yang informatif.</center>

## Pengertian Algoritma

<p>Pada collision simulator ini, digunakannya 2 algoritma untuk menentukan collision. Yaitu menggunakan <b>Brute Force</b> dan <b>Quad Tree</b>.</p>

- Brute Force: Setiap objek lingkaran akan dilakukan pengecekan apakah bola ke-1 dan bola ke-2 melakukan collision. Ketika bola atau objek yang akan dilakukan logic collision mencapai >2000, performa yang akan dihasilkan akan turun drastis dan menyebabkan _lagging_ atau _frame drop_.
- Quad Tree: Quad tree yang dapat dimengerti sebagai 4 (empat). Cara kerja dari Quad Tree itu sendiri adalah dengan membagi menjadi 4 kuadran. Dari pengecekan setiap objek, Quad Tree tidak melakukan pengecekan seperti Brute Force. Quad Tree melakukan pengecekan pada kuadran yang sama, pada program simulator ini, ketika bola atau objek >2000, akan membuat sub-ruang lebih kecil sehingga performa yang dihasilkan jauh lebih efisien daripada menggunakan metode Brute Force.

## Features

- Hold kiri pada mouse akan mengeluarkan bola
- Hold kanan pada mouse akan mengeluarkan 3 bola sekaligus.
- FPS Counter
- Counter Bola
- Toggle untuk mengganti 2 algoritma (Brute Force atau QTree)
- Toggle 'R' untuk reset bola
- Toggle 'G' untuk show/hide QTree Grid
- Toggle 'B' untuk mengganti 2 algoritma collision

## Demonstration

<img src="assets/demo_strukdat.gif" alt="VIDEO_DEMONSTRATION"/>

## Installation

- Collision simulator ini membutuhkan Raylib. Kamu bisa cek Raylib [disini](https://www.raylib.com/)
- Buka CMD dan tulis ".\build.bat" atau buka file build.bat
- Terminal akan menunjukkan bahwa instalasi berhasil atau tidak.
- Jika berhasil, tulis ".\bin\collision-sim.exe" pada CMD.
- Aplikasi akan terbuka. Enjoy 😊

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

## Code Snippets

Kedua snippet dibawah dapat diakses pada folder `src/scripts/UpdateBall.cpp` <br>
Kode dibawah adalah dimana algoritma Brute Force berfungsi.

```cpp
void UpdateBall::resolveCollision(Ball &bola1, Ball &bola2)
{
    float jarakMinimumBola = bola1.radius + bola2.radius;

    float jarakXBola1dan2 = bola2.position.x - bola1.position.x;
    float jarakYBola1dan2 = bola2.position.y - bola1.position.y;

    float jarakKuadrat = jarakXBola1dan2 * jarakXBola1dan2 + jarakYBola1dan2 * jarakYBola1dan2;
    float jarak = sqrtf(jarakKuadrat);

    if (jarak < jarakMinimumBola && jarak > 0.0f)
    {
        float unitVektorX = jarakXBola1dan2 / jarak;
        float unitVektorY = jarakYBola1dan2 / jarak;

        float skalarHasil = (bola1.velocity.x - bola2.velocity.x) * unitVektorX + (bola1.velocity.y - bola2.velocity.y) * unitVektorY;

        bola1.velocity.x -= skalarHasil * unitVektorX;
        bola1.velocity.y -= skalarHasil * unitVektorY;

        bola2.velocity.x += skalarHasil * unitVektorX;
        bola2.velocity.y += skalarHasil * unitVektorY;

        // Overlap issue
        float overlap = jarakMinimumBola - jarak;
        float geserBola = overlap * 0.8f;

        bola1.position.x -= unitVektorX * geserBola;
        bola1.position.y -= unitVektorY * geserBola;

        bola2.position.x += unitVektorX * geserBola;
        bola2.position.y += unitVektorY * geserBola;
    }
}

void UpdateBall::bruteForceCollision(std::vector<Ball> &balls)
{
    size_t bola = balls.size();

    for (size_t i = 0; i < bola; i++)
    {
        for (size_t j = i + 1; j < bola; j++)
        {
            resolveCollision(balls[i], balls[j]);
        }
    }
}
```

Kode dibawah adalah pengaplikasian dari metode algoritma Quad Tree. Lebih detail bisa dilihat pada `src/include/QuadTree.hpp`.

```cpp
void UpdateBall::quadtreeCollision(std::vector<Ball> &balls)
{
    Rectangle boundary = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};
    QNode qtree(boundary, 6);

    for (auto &b : balls)
        qtree.insert(&b);

    if (SHOW_QTREE_GRID)
        qtree.draw();

    // Sama, cek collision.
    for (size_t i = 0; i < balls.size(); i++)
    {
        Ball &bola1 = balls[i];

        Rectangle range = {
            bola1.position.x - bola1.radius * 2,
            bola1.position.y - bola1.radius * 2,
            bola1.radius * 4,
            bola1.radius * 4};

        std::vector<Ball *> candidates;
        qtree.query(range, candidates);

        for (Ball *bola2 : candidates)
        {
            if (&bola1 == bola2)
                continue;
            resolveCollision(bola1, *bola2);
        }
    }
}
```

## Installation

- Collision simulator ini membutuhkan Raylib. Kamu bisa cek Raylib [disini](https://www.raylib.com/)
- Buka CMD dan tulis ".\build.bat" atau buka file build.bat
- Terminal akan menunjukkan bahwa instalasi berhasil atau tidak.
- Jika berhasil, tulis ".\bin\collision-sim.exe" pada CMD.
- Aplikasi akan terbuka. Enjoy 😊

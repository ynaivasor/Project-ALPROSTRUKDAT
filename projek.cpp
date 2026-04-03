#include <iostream>
#include <iomanip>
using namespace std;

struct Driver
{
    string nama;
    string kendaraan;
    string platNomer;
    int rating;
};

struct NodeDriver
{
    Driver data;
    NodeDriver *prev;
    NodeDriver *next;
};

NodeDriver *headDriver = nullptr;
NodeDriver *tailDriver = nullptr;

struct pesanan
{
    string namaPemesan;
    string driverDipilih;
    string lokasiJemput;
    string lokasiTujuan;
    float jarak;
};

struct queue
{
    pesanan data;
    queue *next;
};

queue *depan = nullptr;
queue *belakang = nullptr;

int hitungjumlahdriver()
{
    FILE *file;
    char line[256];
    int jumlah_driver = 0;

    file = fopen("driver.txt", "r");

    if (file == NULL)
    {
        printf("Gagal membuka file driver.txt dalam fungsi hitungjumlahdriver()\n");
        return -1;
    }

    while (fgets(line, sizeof(line), file) != NULL)
    {
        jumlah_driver++;
    }

    fclose(file);

    return jumlah_driver;
}

void tampilkanDriver(Driver daftarDriver[], int jumlah)
{
    if (jumlah == 0)
    {
        cout << "Daftar driver kosong." << endl;
        return;
    }

    cout << "\n=== DAFTAR DRIVER ===" << endl;

    cout << "+-----+----------------------+----------------------+-----------------+--------+" << endl;
    cout << "| No  | Nama                 | Kendaraan            | Plat Nomor      | Rating |" << endl;
    cout << "+-----+----------------------+----------------------+-----------------+--------+" << endl;

    for (int i = 0; i < jumlah; i++)
    {
        cout << "| " << setw(3) << i + 1 << " "
             << "| " << setw(20) << daftarDriver[i].nama
             << "| " << setw(20) << daftarDriver[i].kendaraan
             << "| " << setw(15) << daftarDriver[i].platNomer
             << "| " << setw(6) << daftarDriver[i].rating << " |" << endl;
    }

    cout << "+-----+----------------------+----------------------+-----------------+--------+" << endl;
}

void urutkanBerdasarkanNama(Driver *arr, int jumlah, bool ascending)
{
    for (int i = 0; i < jumlah - 1; i++)
    {
        for (int j = i + 1; j < jumlah; j++)
        {
            if (ascending)
            {
                if (arr[i].nama > arr[j].nama)
                {
                    swap(arr[i], arr[j]);
                }
            }
            else
            {
                if (arr[i].nama < arr[j].nama)
                {
                    swap(arr[i], arr[j]);
                }
            }
        }
    }
}

void urutkanBerdasarkanRating(Driver *arr, int jumlah, bool descending)
{
    for (int i = 0; i < jumlah - 1; i++)
    {
        for (int j = i + 1; j < jumlah; j++)
        {
            if (descending)
            {
                if (arr[i].rating < arr[j].rating)
                {
                    swap(arr[i], arr[j]);
                }
            }
            else
            {
                if (arr[i].rating > arr[j].rating)
                {
                    swap(arr[i], arr[j]);
                }
            }
        }
    }
}

int cariDriver(Driver arr[], int jumlah)
{
    if (jumlah == 0)
    {
        cout << "Data driver kosong." << endl;
        return -1;
    }

    string namaDicari;
    cout << "Masukkan nama driver yang ingin dicari: ";
    getline(cin, namaDicari);

    int awal = 0, akhir = jumlah - 1;
    while (awal <= akhir)
    {
        int mid = (awal + akhir) / 2;
        if (arr[mid].nama == namaDicari)
        {
            cout << "=== Data Driver Ditemukan ===" << endl;
            cout << "Nama\t      : " << arr[mid].nama << endl;
            cout << "Kendaraan\t : " << arr[mid].kendaraan << endl;
            cout << "Plat Nomor\t: " << arr[mid].platNomer << endl;
            cout << "Rating\t    : " << arr[mid].rating << endl;
            return mid;
        }
        else if (namaDicari < arr[mid].nama)
        {
            akhir = mid - 1;
        }
        else
        {
            awal = mid + 1;
        }
    }

    cout << "Driver dengan nama " << namaDicari << " tidak ditemukan." << endl;
    return -1;
}

void tambahKeLinkedListDriver(Driver driverBaru)
{
    NodeDriver *nodeBaru = new NodeDriver;
    nodeBaru->data = driverBaru;
    nodeBaru->prev = nullptr;
    nodeBaru->next = nullptr;

    if (headDriver == nullptr)
    {
        headDriver = tailDriver = nodeBaru;
    }
    else
    {
        tailDriver->next = nodeBaru;
        nodeBaru->prev = tailDriver;
        tailDriver = nodeBaru;
    }
}

void editDriver()
{
    if (headDriver == nullptr)
    {
        cout << "Data driver kosong.\n";
        return;
    }

    string namaEdit;
    cout << "Masukkan nama driver yang ingin diedit: ";
    getline(cin, namaEdit);

    NodeDriver *current = headDriver;
    while (current != nullptr)
    {
        if (current->data.nama == namaEdit)
        {
            cout << "--- Data ditemukan, silakan edit ---\n";
            cout << "Masukkan Nama Baru\t\t: ";
            getline(cin, current->data.nama);
            cout << "Masukkan Jenis Kendaraan Baru\t: ";
            getline(cin, current->data.kendaraan);
            cout << "Masukkan Plat Nomor Baru\t: ";
            getline(cin, current->data.platNomer);

            cout << "Masukkan Rating Baru (1-5)\t: ";
            cin >> current->data.rating;
            cin.ignore();
            cout << "Data driver berhasil diupdate.\n";
            return;
        }
        current = current->next;
    }

    cout << "Driver tidak ditemukan.\n";
}

void hapusDriver()
{
    if (headDriver == nullptr)
    {
        cout << "Data driver kosong.\n";
        return;
    }

    string namaHapus;
    cout << "Masukkan nama driver yang ingin dihapus: ";
    getline(cin, namaHapus);

    NodeDriver *current = headDriver;
    while (current != nullptr)
    {
        if (current->data.nama == namaHapus)
        {
            if (current->prev != nullptr)
                current->prev->next = current->next;
            else
                headDriver = current->next;

            if (current->next != nullptr)
                current->next->prev = current->prev;
            else
                tailDriver = current->prev;

            delete current;
            cout << "Data driver berhasil dihapus.\n";
            return;
        }
        current = current->next;
    }

    cout << "Driver tidak ditemukan.\n";
}

void tambahDriver(Driver daftarDriver[], int &jumlah)
{
    int jumlahBaru;
    cout << "Masukkan jumlah driver yang ingin ditambahkan : ";
    cin >> jumlahBaru;
    cin.ignore();

    for (int i = 0; i < jumlahBaru; i++)
    {
        cout << "\nMasukkan data Driver ke-" << (jumlah + 1) << endl;
        cout << "Nama Driver\t                 : ";
        getline(cin, daftarDriver[jumlah].nama);
        cout << "Jenis Kendaraan\t             : ";
        getline(cin, daftarDriver[jumlah].kendaraan);
        cout << "Plat Nomor\t                  : ";
        getline(cin, daftarDriver[jumlah].platNomer);
        cout << "Rating (1-5)\t                : ";
        cin >> daftarDriver[jumlah].rating;
        cin.ignore();

        tambahKeLinkedListDriver(daftarDriver[jumlah]);
        jumlah++;
    }
}

void menuLihatDriver(Driver daftarDriver[], int jumlahDriver)
{
    int pilihanSort, urutan;
    cout << jumlahDriver << " driver tersedia.\n";
    cout << "\n--- Lihat Driver ---\n";
    cout << "1. Urutkan berdasarkan Nama\n";
    cout << "2. Urutkan berdasarkan Rating\n";
    cout << "Pilihan: ";
    cin >> pilihanSort;
    cin.ignore();

    cout << "1. Urutkan dari atas\n";
    cout << "2. Urutkan dari bawah\n";
    cout << "Pilihan: ";
    cin >> urutan;
    cin.ignore();

    bool ascending = (urutan == 1);
    bool descending = (urutan == 1);

    if (pilihanSort == 1)
    {
        urutkanBerdasarkanNama(daftarDriver, jumlahDriver, ascending);
    }
    else if (pilihanSort == 2)
    {
        urutkanBerdasarkanRating(daftarDriver, jumlahDriver, descending);
    }
    else
    {
        cout << "Pilihan sorting tidak valid.\n";
        return;
    }

    tampilkanDriver(daftarDriver, jumlahDriver);
}

void buatPesanan()
{
    queue *baru = new queue;
    cout << "Masukkan Nama Pemesan\t: ";
    getline(cin, baru->data.namaPemesan);
    cout << "Masukkan Nama Driver yang Dipilih\t: ";
    getline(cin, baru->data.driverDipilih);
    cout << "Masukkan Lokasi Jemput\t: ";
    getline(cin, baru->data.lokasiJemput);
    cout << "Masukkan Lokasi Tujuan\t: ";
    getline(cin, baru->data.lokasiTujuan);
    cout << "Masukkan Jarak (km)\t: ";
    cin >> baru->data.jarak;
    cin.ignore();
    baru->next = nullptr;

    if (belakang == nullptr)
    {
        depan = belakang = baru;
    }
    else
    {
        belakang->next = baru;
        belakang = baru;
    }

    cout << "Pesanan berhasil dibuat!" << endl;
}

void lihatAntrian()
{
    if (depan == nullptr)
    {
        cout << "Antrian pesanan kosong." << endl;
        return;
    }

    cout << "\n=== ANTRIAN PESANAN ===\n"
         << endl;

    cout << "+-----+--------------------+--------------------+--------------------+--------------------+------------+" << endl;
    cout << "| No  | Pemesan            | Driver             | Jemput             | Tujuan             | Jarak (km) |" << endl;
    cout << "+-----+--------------------+--------------------+--------------------+--------------------+------------+" << endl;

    queue *temp = depan;
    int no = 1;
    while (temp != nullptr)
    {
        cout << "| " << setw(3) << left << no++ << " "
             << "| " << setw(18) << left << temp->data.namaPemesan
             << "| " << setw(18) << left << temp->data.driverDipilih
             << "| " << setw(18) << left << temp->data.lokasiJemput
             << "| " << setw(18) << left << temp->data.lokasiTujuan
             << "| " << setw(10) << right << fixed << setprecision(1) << temp->data.jarak << " |" << endl;

        temp = temp->next;
    }

    cout << "+-----+--------------------+--------------------+--------------------+--------------------+------------+" << endl;
}

void batalkanPesanan()
{
    if (depan == nullptr)
    {
        cout << "Tidak ada pesanan yang bisa dibatalkan." << endl;
        return;
    }

    queue *hapus = depan;
    depan = depan->next;
    if (depan == nullptr)
    {
        belakang = nullptr;
    }
    cout << "Pesanan atas nama " << hapus->data.namaPemesan << " dibatalkan." << endl;
    delete hapus;
}

void simpanDriverKeFile(Driver daftar[], int &jumlah)
{
    FILE *file = fopen("driver.txt", "w");
    if (!file)
    {
        cout << "Gagal menyimpan file.\n";
        return;
    }
    for (int i = 0; i < jumlah; i++)
    {
        fprintf(file, "%s;%s;%s;%d\n",
                daftar[i].nama.c_str(),
                daftar[i].kendaraan.c_str(),
                daftar[i].platNomer.c_str(),
                daftar[i].rating);
    }
    fclose(file);
    cout << "Data driver disimpan ke file.\n";
}

void loadDriverDariFile(Driver daftar[], int &jumlah)
{
    FILE *file = fopen("driver.txt", "r");
    if (!file)
        return;

    char nama[100], kendaraan[100], platNomer[20];
    int rating;

    while (fscanf(file, "%99[^;];%99[^;];%19[^;];%d\n", nama, kendaraan, platNomer, &rating) == 4)
    {
        daftar[jumlah].nama = string(nama);
        daftar[jumlah].kendaraan = string(kendaraan);
        daftar[jumlah].platNomer = string(platNomer);
        daftar[jumlah].rating = rating;
        tambahKeLinkedListDriver(daftar[jumlah]);
        jumlah++;
        if (jumlah >= 50)
            break;
    }

    fclose(file);
    cout << "Data driver berhasil dimuat dari file.\n";
}

void simpanPesananKeFile()
{
    FILE *file = fopen("pesanan.txt", "w");
    if (!file)
    {
        cout << "Gagal menyimpan file pesanan.\n";
        return;
    }

    queue *temp = depan;
    while (temp != nullptr)
    {
        fprintf(file, "%s;%s;%s;%s;%.2f\n",
                temp->data.namaPemesan.c_str(),
                temp->data.driverDipilih.c_str(),
                temp->data.lokasiJemput.c_str(),
                temp->data.lokasiTujuan.c_str(),
                temp->data.jarak);
        temp = temp->next;
    }

    fclose(file);
    cout << "Data pesanan disimpan ke file.\n";
}

void loadPesananDariFile()
{
    FILE *file = fopen("pesanan.txt", "r");
    if (!file)
        return;

    char nama[100], driver[100], jemput[100], tujuan[100];
    float jarak;

    while (fscanf(file, "%[^;];%[^;];%[^;];%[^;];%f\n",
                  nama, driver, jemput, tujuan, &jarak) == 5)
    {
        queue *baru = new queue;
        baru->data.namaPemesan = nama;
        baru->data.driverDipilih = driver;
        baru->data.lokasiJemput = jemput;
        baru->data.lokasiTujuan = tujuan;
        baru->data.jarak = jarak;
        baru->next = nullptr;

        if (!belakang)
        {
            depan = belakang = baru;
        }
        else
        {
            belakang->next = baru;
            belakang = baru;
        }
    }

    fclose(file);
    cout << "Data pesanan berhasil dimuat dari file.\n";
}

void sinkronisasiArrayDariLinkedList(Driver *daftar, int &jumlah)
{
    NodeDriver *current = headDriver;
    jumlah = 0;
    while (current != nullptr && jumlah < 50)
    {
        daftar[jumlah] = current->data;
        jumlah++;
        current = current->next;
    }
}

void menuUser(Driver daftarDriver[], int jumlahDriver)
{
    int pilihanUser;
    do
    {
        cout << "\n=== MENU PENGGUNA ===" << endl;
        cout << "+----+----------------------------+" << endl;
        cout << "| No |          Pilihan          |" << endl;
        cout << "+----+----------------------------+" << endl;
        cout << "| 1  | Lihat Daftar Driver        |" << endl;
        cout << "| 2  | Buat Pesanan               |" << endl;
        cout << "| 3  | Lihat Antrian Pesanan      |" << endl;
        cout << "| 4  | Batalkan Pesanan           |" << endl;
        cout << "| 5  | Logout                     |" << endl;
        cout << "+----+----------------------------+" << endl;
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihanUser;
        cin.ignore();

        switch (pilihanUser)
        {
        case 1:
            tampilkanDriver(daftarDriver, jumlahDriver);
            break;
        case 2:
            buatPesanan();
            break;
        case 3:
            lihatAntrian();
            break;
        case 4:
            batalkanPesanan();
            break;
        case 5:
            return;
        default:
            cout << "Pilihan tidak valid." << endl;
        }

        cout << "Kembali ke menu pengguna? (Y/N): ";
        string kembali;
        getline(cin, kembali);
        if (kembali != "Y" && kembali != "y")
            return;
    } while (true);
}

void menuAdmin(Driver daftarDriver[], int jumlahDriver)
{
    int pilihanAdmin;
    do
    {
        cout << "\n=== MENU ADMIN ===" << endl;
        cout << "+----+----------------------------+" << endl;
        cout << "| No |          Pilihan          |" << endl;
        cout << "+----+----------------------------+" << endl;
        cout << "| 1  | Lihat Data Driver          |" << endl;
        cout << "| 2  | Cari Nama Driver           |" << endl;
        cout << "| 3  | Edit Data Driver           |" << endl;
        cout << "| 4  | Hapus Data Driver          |" << endl;
        cout << "| 5  | Tambah Data Driver         |" << endl;
        cout << "| 6  | Logout                     |" << endl;
        cout << "+----+----------------------------+" << endl;
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihanAdmin;
        cin.ignore();

        switch (pilihanAdmin)
        {
        case 1:
            menuLihatDriver(daftarDriver, jumlahDriver);
            break;
        case 2:
            cariDriver(daftarDriver, jumlahDriver);
            break;
        case 3:
            editDriver();
            sinkronisasiArrayDariLinkedList(daftarDriver, jumlahDriver);
            break;
        case 4:
            hapusDriver();
            sinkronisasiArrayDariLinkedList(daftarDriver, jumlahDriver);
            break;
        case 5:
            tambahDriver(daftarDriver, jumlahDriver);
            break;
        case 6:
            return;
        default:
            cout << "Pilihan tidak valid." << endl;
        }

        cout << "Kembali ke menu admin? (Y/N): ";
        string kembali;
        getline(cin, kembali);
        if (kembali != "Y" && kembali != "y")
            return;
    } while (true);
}

void menuUtama(int jumlahDriver, Driver *daftarDriver)
{

    int pilihRole;

    string username, password;
    string adminUser = "admin";
    string adminPass = "12345";
    string kembali;

    do
    {
        cout << "\n=== SELAMAT DATANG DI PROGRAM SI-OJOL ===" << endl;
        cout << "+----+-------------------+" << endl;
        cout << "| No |      Pilihan      |" << endl;
        cout << "+----+-------------------+" << endl;
        cout << "| 1  | Admin             |" << endl;
        cout << "| 2  | Pengguna          |" << endl;
        cout << "| 3  | Keluar            |" << endl;
        cout << "+----+-------------------+" << endl;
        cout << "Masukkan pilihan Anda: ";

        cin >> pilihRole;
        cin.ignore();

        if (pilihRole == 1)
        {
            while (true)
            {
                cout << "Login Admin" << endl;
                cout << "Masukkan Username\t: ";
                getline(cin, username);
                cout << "Masukkan Password\t: ";
                getline(cin, password);

                if (username == adminUser && password == adminPass)
                {
                    cout << "Login berhasil!\n";
                    break;
                }
                else
                {
                    cout << "Username atau password salah. Coba lagi.\n";
                }
            }
            menuAdmin(daftarDriver, jumlahDriver);
        }
        else if (pilihRole == 2)
        {
            menuUser(daftarDriver, jumlahDriver);
        }
        else if (pilihRole == 3)
        {
            cout << "Terima kasih telah menggunakan program ini." << endl;
            return;
        }
        else
        {
            cout << "Pilihan tidak valid." << endl;
        }

        cout << "\nKembali ke menu utama? (Y/N): ";
        getline(cin, kembali);
    } while (kembali == "Y" || kembali == "y");

    cout << "Terima kasih telah menggunakan program ini." << endl;
}

int main()
{
    Driver daftarDriver[50];
    int jumlahDriver = 0;

    loadDriverDariFile(daftarDriver, jumlahDriver);

    loadPesananDariFile();

    menuUtama(jumlahDriver, daftarDriver);

    sinkronisasiArrayDariLinkedList(daftarDriver, jumlahDriver);
    simpanDriverKeFile(daftarDriver, jumlahDriver);
    simpanPesananKeFile();

    return 0;
}

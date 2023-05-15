#include <stdio.h>
#include <stdlib.h>

// kuyruk elemanini belirten struct
struct kuyruk_elemani
{
    int veri;
    struct kuyruk_elemani *sonraki;
};

// eleman ekleyen fonksiyon siranin basini ve sonunu pointer to pointer olarak alir
void eleman_ekle(struct kuyruk_elemani **bas, struct kuyruk_elemani **son)
{

    int veri;
    // yeni eleman icin yer ayirir
    struct kuyruk_elemani *eleman = malloc(sizeof(struct kuyruk_elemani));
    printf("\nveriyi tamsayi olarak giriniz : ");
    scanf("%d", &veri);
    // girilen veriyi elemana ekler
    eleman->veri = veri;
    eleman->sonraki = NULL;
    // eger kuyrugun sonu yoksa kuyruk yok demektir
    if (*son == NULL)
    {
        // ilk eklenen eleman hem bas hem de son olur
        *bas = eleman;
        *son = eleman;
        // fonksiyon isini bitirir
        return;
    }
    // eger kuyrugun sonu varsa eleman var demektir
    // son eleman yeni elemana isaret eder ve yeni eleman son eleman olur
    (*son)->sonraki = eleman;
    *son = eleman;
    return;
}

// elemani dequeue eden fonksiyon
void eleman_cikar(struct kuyruk_elemani **son, struct kuyruk_elemani **bas)
{
    // eger bas yoksa eleman da yok demektir
    if (*bas == NULL)
    {
        // kullanici bilgilendirilir
        printf("\nhenuz bir eleman eklenmedi\n");
        return;
    }
    // eger bas ve son ayni veriye isaret ediyorsa tek eleman var demektir
    if (&(**bas) == &(**son))
    {
        printf("\ncikan tamsayi %d dir\n sira bitmistir\n", (*bas)->veri);
        // elemanin kapladigi alan serbest birakilir, bas ve son hicbir seye isaret etmemelidir
        free(*bas);
        *bas = NULL;
        *son = NULL;
        return;
    }
    // eger kuyruk var olmakla birlikte birden fazla elemani da varsa
    // siranin basindaki elemana isaret eden pointer
    struct kuyruk_elemani *temp = *bas;

    // kullaniciya veri bildirilir
    printf("\ncikan tamsayi %d dir\n", (*bas)->veri);
    // siranin basindaki eleman ikinci siradaki eleman olur
    *bas = (*bas)->sonraki;
    // eskiden siranin basi olan elemanin kapladigi alan serbest birakilir
    free(temp);
    return;
}

// sirayi temsil edecek ciktiyi verecek fonksiyon
void goruntule(struct kuyruk_elemani **bas)
{

    // teker teker siranin elemanlarina isaret edecek olan isaretci
    struct kuyruk_elemani *temp = *bas;
    // o an isaret edilen elemanin barindirdigi degeri depolayacak degisken
    int veri;
    // sirayi belirten degisken
    int sira = 1;
    // eger bas bir seye isaret etmiyorsa sira yok demektir
    if (*bas == NULL)
    {
        // kullanici bilgilendirilir
        printf("\nsira yok\n");
        return;
    }
    printf("\n==================\n");
    // isaret edilecek eleman oldugu surece devam eden dongu
    do
    {
        // elemanin icerdigi veri
        veri = temp->veri;
        // temsili cikti
        printf("(%d)[ %d ]", sira, veri);
        // eger gecerli elemandan sonra bir daha eleman varsa ok isareti ciktisi eklenir
        if (temp->sonraki != NULL)
            printf(" -> ");
        // gecerli elemandan sonraki elemana gecilir
        temp = temp->sonraki;
        // sira 1 arttirilir
        sira++;

    } while (temp != NULL);
    printf("\n==================\n");
}

int main()
{
    struct kuyruk_elemani *bas = NULL;
    struct kuyruk_elemani *son = NULL;

    int secenek;
    int yurut = 1;
    // ana program
    while (yurut)
    {
        printf("Asagidaki islemlerden birini seciniz : \n");
        printf("1 . Ekleme (enqueue)\n");
        printf("2 . Cikarma (dequeue)\n");
        printf("3 . Goruntuleme\n");
        printf("4 . Cikis\n");
        printf(">");
        scanf("%d", &secenek);

        switch (secenek)
        {
        case 1:
            eleman_ekle(&bas, &son);
            break;

        case 2:
            eleman_cikar(&son, &bas);
            break;
        case 3:
            goruntule(&bas);
            break;
        case 4:
            yurut = 0;
            break;

        default:
            printf("Gecersiz giris!");
            break;
        }
    }
    return 0;
}
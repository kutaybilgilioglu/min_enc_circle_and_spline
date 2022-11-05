#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
    FILE *file;
    file=fopen("koordinat.txt","r"); //Dosyayi acar
    int a[15][2],noktasayisi=0,i=0,j=0;
    char sayix[20],sayiy[20];
    if((file=fopen("koordinat.txt","r"))==NULL)
    {
        printf("Dosya sistemde bulunmadi...");
        return 0;
    }
    while(!feof(file)) //Dosyanin sonuna gelene kadar dosya icindekileri okur
    {
        fscanf(file,"%d%d",&a[i][0],&a[i][1]);
        i++;
        noktasayisi=i;
    }
    initwindow(1536,864,""); //graphics.h icin pencere
    setcolor(YELLOW); //renk belirler (setcolor(): graphics.h fonksiyonu)
    line(768,0,768,864); //koordinat duzlemlerini cizer
    line(336,432,1200,432);
    for(j=-20; j<=20; j=j+5) //eksenler ustune sayilari yazdirir
    {
        if(j==0)
            continue;
        sprintf(sayix,"%d",j);
        outtextxy(760+(21*j),404,sayix);
        outtextxy(784,424-(21*j),sayix);
    }
    for(int l=1; l<=20; l++) //x ve y eksenlerine esit 21 pixel aralikla kisa cizgiler cizer (line(): graphics.h fonksiyonu)
    {
        line(762,432-(21*l),774,432-(21*l));
        line(762,432+(21*l),774,432+(21*l));
        line(768-(21*l),426,768-(21*l),438);
        line(768+(21*l),426,768+(21*l),438);
        if(l%5==0)
        {
            line(756,432-(21*l),780,432-(21*l));
            line(756,432+(21*l),780,432+(21*l));
            line(768-(21*l),420,768-(21*l),444);
            line(768+(21*l),420,768+(21*l),444);
        }
    }
    int sayac=0;
    double cap=0,r=0,h=0,merkezx=0,merkezy=0,D=0,x3=0,y3=0,kontrol=0,x1=0,y1=0,x2=0,y2=0;
    setcolor(GREEN); //renk belirler
    for(i=0; i<noktasayisi; i++){
        bar(766+21*a[i][0],430-21*a[i][1],770+21*a[i][0],434-21*a[i][1]); //noktalari grafik ustunde gosterir
        line(768+21*a[i][0],432-21*a[i][1],768+21*a[i][0],432); //noktalardan eksenlere dik cizgi indirir
        line(768+21*a[i][0],432-21*a[i][1],768,432-21*a[i][1]);
        sprintf(sayix,"(%d ",a[i][0]); //noktalari (x,y) seklinde grafik ustunde gosterir
        sprintf(sayiy,", %d)",a[i][1]);
        outtextxy(771+21*a[i][0],415-21*a[i][1],sayix);
        outtextxy(795+21*a[i][0],415-21*a[i][1],sayiy);
        for(j=0; j<noktasayisi; j++)
        {
            if(cap<sqrt(pow((a[i][0]-a[j][0]),2)+pow((a[i][1]-a[j][1]),2)))  //birbirine en uzak 2 noktayi bulan dongu
            {
                cap=sqrt(pow((a[i][0]-a[j][0]),2)+pow((a[i][1]-a[j][1]),2));
                x1=a[i][0]; // en uzak noktalar koordinatlari
                y1=a[i][1];
                x2=a[j][0];
                y2=a[j][1];
            }
        }
    }
    for(i=0; i<noktasayisi; i++)
    {
        if((cap/2)>=sqrt(pow(a[i][0]-((x1+x2)/2),2)+pow(a[i][1]-((y1+y2)/2),2))) // en uzak 2 noktanin cap oldugu cember tum noktalari kapsar mi kontrolu
            sayac++;
    }
    setcolor(WHITE);
    if(sayac==noktasayisi)
    {
        circle(768+21*(x1+x2)/2,432-21*(y1+y2)/2,cap/2*21); // en uzak 2 nokta capsa cemberi çizdirir
        line(768+x2*21,432-y2*21,768+((x1+x2)/2)*21,432-((y1+y2)/2)*21); //Yaricap cizdirir
        bar(765+21*((x1+x2)/2),429-21*((y1+y2)/2),771+21*((x1+x2)/2),435-21*((y1+y2)/2)); //Merkezi gosterir
        outtextxy(768+((x1+x2)/2)*21,435-((y1+y2)/2)*21,"M");
        printf("Cemberin Yaricapi = %.3f\nCemberin Merkezi = (%.3f , %.3f)",cap/2,((x1+x2)/2),((y1+y2)/2));
    }
    else
    {
        for(i=0; i<noktasayisi; i++)
        {       //en uzak 2 noktaya en uzak 3. noktayi bulur
            kontrol = sqrt(pow((((y2-y1)*(a[i][0]))+((x1-x2)*(a[i][1]))+(y1*x2-x1*y2)),2))/(sqrt(pow(y2-y1,2))+pow(x1-x2,2));
            if(h<kontrol)
            {
                h=kontrol;
                x3=a[i][0]; // en uzak 3. nokta
                y3=a[i][1];
            }
        }
        D=2*(x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2)); //cevrel cember cizmek icin gerekli
        merkezx = ((pow(y1,2)+pow(x1,2))*(y2-y3)+ (pow(y2,2)+pow(x2,2))*(y3-y1)+(pow(y3,2)+pow(x3,2))*(y1-y2))/D; //cevrel cemberin merkezi
        merkezy = ((pow(y1,2)+pow(x1,2))*(x3-x2)+ (pow(y2,2)+pow(x2,2))*(x1-x3)+(pow(y3,2)+pow(x3,2))*(x2-x1))/D;
        r=sqrt(pow(x2-merkezx,2)+pow(y2-merkezy,2)); //Yaricapi hesaplar
        circle(768+merkezx*21,432-merkezy*21,r*21); // Cember cizdirir
        line(768+x3*21,432-y3*21,768+merkezx*21,432-merkezy*21); //Yaricap cizdirir
        bar(765+21*merkezx,429-21*merkezy,771+21*merkezx,435-21*merkezy); //Merkezi gosterir
        outtextxy(768+merkezx*21,435-merkezy*21,"M");
        printf("Cemberin Yaricapi = %.3f\nCemberin Merkezi = (%.3f , %.3f)",r,merkezx,merkezy);
    }
    getch(); //Spline'ý cizdirmek icin tusa basilmasini bekler
    int tempx=0,tempy=0,tx=a[0][0]-1,ty=a[0][1],zx=a[noktasayisi-1][0]+1,zy=a[noktasayisi-1][1],ix=0,iy=0,kx=0,ky=0;
    double u=0,pixx=0,pixy=0;
    for(i=0; i<noktasayisi; i++) //Bubble Sort algoritmasi=>x ve y leri kucukten buyuge sýraladým(b-spline icin)
    {
        for(int j=1; j<noktasayisi-i; j++)
        {
            if(a[j-1][0]>a[j][0])
            {
                tempx=a[j][0];
                tempy=a[j][1];
                a[j][0]=a[j-1][0];
                a[j][1]=a[j-1][1];
                a[j-1][0]=tempx;
                a[j-1][1]=tempy;
            }
        }
    }
    for(i=0; i<noktasayisi-1; i++)
    {
        u = 0.001; // u iki nokta arasinda cizilecek spline'in parametresi (0<= u <=1)
        for(double k=0; k<=1; k=k+u) //k: her donuste u kadar artan parametre
        {
            if(i==0)
            {
                ix=tx; //tx ve ty hayali noktalar (formul ýcýn gerekli, raporda detayi var)
                iy=ty;
                kx=a[i+2][0];
                ky=a[i+2][1];
            }
            else if(i==noktasayisi-2)
            {
                kx=zx; //zx zy hayali noktalar (formul ýcýn gerekli, raporda detayi var)
                ky=zy;
                ix=a[i-1][0];
                iy=a[i-1][1];
            }
            else
            {
                ix=a[i-1][0]; //iki nokta arasi spline icin gerekli degiskenler(raporda detayi var)
                iy=a[i-1][1];
                kx=a[i+2][0];
                ky=a[i+2][1];
            }
            //B-spline'in cizilecegi koordinatlari hesaplar.
            pixx=((pow(1-k,3)*ix)+((3*pow(k,3)-6*pow(k,2)+4)*a[i][0])+((-3*pow(k,3)+3*pow(k,2)+3*k+1)*a[i+1][0])+pow(k,3)*kx)/6;
            pixy=((pow(1-k,3)*iy)+((3*pow(k,3)-6*pow(k,2)+4)*a[i][1])+((-3*pow(k,3)+3*pow(k,2)+3*k+1)*a[i+1][1])+pow(k,3)*ky)/6;
            putpixel((int)(768+(pixx*21)),(int)(432-(pixy*21)),RED); // gerekli koordinatlari boyar
        }
    }
    getch();
    closegraph();
    fclose(file); //Dosyayi kapatir
    return 1;
}

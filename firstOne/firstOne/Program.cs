using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System;
using System.IO;
using RozszerzenieLib;

namespace firstOne
{
    class Program
    {
        

        static void iteracyjny(string dirName)
        {
            
            DirectoryInfo di = new DirectoryInfo(dirName);
            foreach(var file in di.GetFiles()) 
            { 
                Console.WriteLine(file.Name);
                
            }
        }

        static void rekurencyjny(string sDir, int licznik)
        {
             //rozmiar.rozmiary()
            DirectoryInfo di = new DirectoryInfo(sDir);
            foreach (var file in di.GetFiles())
            {
                for (int i = 0; i < licznik; i++)
                {
                    Console.Write("-");
                }
                Console.WriteLine(file.Name);
            }

            foreach (var directories in di.GetDirectories())
            {
                for (int i = 0; i < licznik; i++)
                {
                    Console.Write("-");
                }

                Console.WriteLine(directories.Name + ":" + directories.rozmiary());
                rekurencyjny(directories.FullName, licznik++);
            }
        }

        static void Main(string[] args)
        {
            iteracyjny("D:\\Pulpit\\");
            //rekurencyjny("D:\\Pulpit\\", 0);
        }
    }

    //static class Rozszerzenie
    //{
    //    public static long rozmiary(this DirectoryInfo str)
    //    {
    //        //DirectoryInfo di = new DirectoryInfo(str);
    //        long rozmiar = 0;

    //        foreach (FileInfo f in str.GetFiles())
    //        {
    //            rozmiar += f.Length;
    //            //Console.WriteLine(f.Length);
    //        }
    //        Console.WriteLine(rozmiar);
    //        return rozmiar;
    //    }
    //}

    //public static class ExtentedMethods //
    //{
    //    public static int licz_znaki(this FileInfo fi, char chr)
    //    {
    //        int count = 0;
    //        using (StreamReader sr = fi.OpenText())
    //        {
    //            string str = "";
    //            while ((str = sr.ReadLine()) != null)
    //            {
    //                count += str.Split(chr).Length - 1;
    //            }
    //        }
    //        return count;
    //    }
    //}
}

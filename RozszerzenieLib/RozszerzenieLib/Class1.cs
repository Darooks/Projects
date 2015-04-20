using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace RozszerzenieLib
{
    public static class Class1
    {
        public static long rozmiary(this DirectoryInfo str)
        {
            //DirectoryInfo di = new DirectoryInfo(str);
            long rozmiar = 0;

            foreach (FileInfo f in str.GetFiles())
            {
                rozmiar += f.Length;
                //Console.WriteLine(f.Length);
            }
            Console.WriteLine(rozmiar);
            return rozmiar;
        }

    }
}

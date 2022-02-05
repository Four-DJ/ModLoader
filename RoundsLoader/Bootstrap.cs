using ModLoader.Attributes;
using ModLoader.Modules;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace ModLoader
{
	public class Bootstrap
	{
		[DllImport("kernel32.dll")]
		private static extern int AllocConsole();

		[DllImport("user32.dll")]
		[return: MarshalAs(UnmanagedType.Bool)]
		private static extern bool SetForegroundWindow(IntPtr hWnd);

		[DllImport("kernel32.dll")]
		private static extern IntPtr GetConsoleWindow();

		private static void ShowConsole()
		{
			SetForegroundWindow(GetConsoleWindow());
		}


		public static void Inject()
		{
			AllocConsole();
			Console.SetOut(new StreamWriter(Console.OpenStandardOutput())
			{
				AutoFlush = true
			});
			Console.SetIn(new StreamReader(Console.OpenStandardInput()));
			Console.Clear();

			Console.Title = "ModLoader|1.0|Four_DJ";
			ShowConsole();
			Log("Init", "Started ModLoader", ConsoleColor.Blue, ConsoleColor.Green);

			GameObject gameObject = new GameObject();
			GameObject.DontDestroyOnLoad(gameObject);

			if (!Directory.Exists("Mods"))
				Directory.CreateDirectory("Mods");
			string[] files = Directory.GetFiles("Mods");
			foreach (string path2 in files)
			{
				if (!(Path.GetExtension(path2) == ".dll"))
				{
					continue;
				}
				Assembly assembly;
				try
				{
					assembly = Assembly.LoadFile(path2);
				}
				catch
				{
					Log("ERROR", $"Failed to Load {Path.GetFileName(path2)}", ConsoleColor.DarkRed, ConsoleColor.Red);
					continue;
				}
				foreach (Type item in from t in assembly.GetTypes()
									  where t.IsSubclassOf(typeof(Mod))
									  select t)
				{
					if (item.GetCustomAttributes(typeof(ModuleInfoAttribute), inherit: true).FirstOrDefault() is ModuleInfoAttribute moduleInfo)
					{
						Mod mod = gameObject.AddComponent(item) as Mod;
						mod.Initialize(moduleInfo);
						Log("Injected", mod.ToString(), ConsoleColor.DarkBlue, ConsoleColor.Yellow);
					}
				}
			}
		}

		public static void Log(string logType, string msg, ConsoleColor typeColor, ConsoleColor msgColor = ConsoleColor.White)
		{
			Console.Write("[");
			Console.ForegroundColor = ConsoleColor.Cyan;
			Console.Write("ModLoader");
			Console.ForegroundColor = ConsoleColor.White;
			Console.Write("] [");
			Console.ForegroundColor = ConsoleColor.Magenta;
			Console.Write(DateTime.Now.ToString("hh:mm:ss.fff"));
			Console.ForegroundColor = ConsoleColor.White;
			Console.Write("] [");
			Console.ForegroundColor = typeColor;
			Console.Write(logType);
			Console.ForegroundColor = ConsoleColor.White;
			Console.Write("] ");
			Console.ForegroundColor = msgColor;
			Console.WriteLine(msg);
			Console.ForegroundColor = ConsoleColor.White;
		}
	}
}
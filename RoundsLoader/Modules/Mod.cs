using ModLoader.Attributes;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace ModLoader.Modules
{
	public class Mod : MonoBehaviour
	{
		public string Name { get; private set; }

		public string Version { get; private set; }

		public string Author { get; private set; }

        public ConsoleColor Color { get; private set; }

		internal void Initialize(ModuleInfoAttribute moduleInfo)
		{
			Name = moduleInfo.Name;
			Version = moduleInfo.Version;
			Author = moduleInfo.Author;
            Color = moduleInfo.Color;

        }

		public void Log(string logType, string msg, ConsoleColor typeColor, ConsoleColor msgColor = ConsoleColor.White)
        {
            Console.Write("[");
            Console.ForegroundColor = Color;
            Console.Write(Name);
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

        public override string ToString()
		{
			return $"{Name} ({Version}) by {Author}";
		}
	}
}

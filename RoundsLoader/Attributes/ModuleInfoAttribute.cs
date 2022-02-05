using System;

namespace ModLoader.Attributes
{
	[AttributeUsage(AttributeTargets.Class, AllowMultiple = false)]
	public class ModuleInfoAttribute : Attribute
	{
		public string Name { get; }

		public string Version { get; }

		public string Author { get; }

		public ConsoleColor Color { get; }

		public ModuleInfoAttribute(string name, string version, string author, ConsoleColor color)
		{
			Name = name;
			Version = version;
			Author = author;
			Color = color;
		}
	}

}

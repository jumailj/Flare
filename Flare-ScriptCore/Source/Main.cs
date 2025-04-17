using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Flare
{

	[StructLayout(LayoutKind.Sequential)]
	public struct Vector3 {
		public float x, y, z;

		public Vector3(float x, float y, float z) {
			this.x = x;
			this.y = y;
			this.z = z;
		}
	}


	
	public static class InternalCalls 
	{
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void NativeLog(string parameter, int value);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void NativeLog_vector(ref Vector3 parameter);


	}
	public class Entity
	{

		public float FloatVar { get; set; }

		public Entity()
		{
			Console.WriteLine("Entity constructor!");
		}

		public void PrintMessage()
		{
			// Console.WriteLine("Hello World from C#!");
			// CppFunction();

			Vector3 pos = new Vector3(11.0f, 20.0f, 30.0f);
			Log( pos);
			Log("This is a native log message!", 0);
		}

		public void PrintInt(int value)
		{
			Console.WriteLine($"C# says: {value}");
			
		}

		public void PrintInts(int value1, int value2)
		{
			Console.WriteLine($"C# says: {value1} and {value2}");
		}

		public void PrintCustomMessage(string message)
		{
			Console.WriteLine($"C# says: {message}");
		}


		private void Log(string parameter, int value){
			InternalCalls.NativeLog(parameter, value);
		}

		private void Log(Vector3 parameter){
			InternalCalls.NativeLog_vector(ref parameter);
		}

	}

}
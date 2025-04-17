using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sandbox {

    internal class Player : Entity{

        void OnCreate(){
            Console.WriteLine("Player.Created!");
        }

        void OnUpdate(float ts){
            Console.WriteLine($"Player.Update: {ts}");

        }

    }

}
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyClassLibrary
{
    public class PersonExecutant : Executant
    {
        public string Name { get; }
        public string Adress { get; }

        public PersonExecutant(Guid id, string name, string adress)
            : base(id)
        {
            Name = name;
            Adress = adress;
        }
    }
}

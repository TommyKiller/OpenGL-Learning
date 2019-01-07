using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyClassLibrary
{
    public class FirmExecutant : Executant
    {
        public string Name { get; }
        public string Head { get; }

        public FirmExecutant(Guid id, string name, string head)
            : base(id)
        {
            Name = name;
            Head = head;
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyClassLibrary
{
    public abstract class Executant
    {
        public Guid ID { get; }

        public Executant(Guid id)
        {
            ID = id;
        }
    }
}

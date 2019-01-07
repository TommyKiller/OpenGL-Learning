using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyClassLibrary.Tasks
{
    public class AddFeature : ProjectTask
    {
        public AddFeature(string description, DateTime deadLine)
            : base(description, deadLine)
        {

        }
    }
}

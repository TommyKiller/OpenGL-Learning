using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyClassLibrary
{
    public class Project
    {
        public Guid ID { get; }
        public List<ProjectTask> Tasks { get; private set; }
    }
}

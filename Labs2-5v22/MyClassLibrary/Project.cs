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
        public string Name { get; }
        public List<ProjectTask> Tasks { get; private set; }
        public static List<Project> Projects { get; }

        public Project(Guid id, string name)
        {
            ID = id;
            Name = name;
            Tasks = new List<ProjectTask>();
        }
    }
}

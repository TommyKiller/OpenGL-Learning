﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyClassLibrary.Tasks
{
    public class EditFeature : ProjectTask
    {
        public EditFeature(string description, DateTime deadLine)
            : base(description, deadLine)
        {

        }
    }
}

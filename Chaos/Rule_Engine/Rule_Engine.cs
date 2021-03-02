using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

namespace Chaos
{
    class Event : Entity
    {
        //The participating entities.
        public List<Entity> Participants;

        //The amount of power that is associated in this event.
        public double Significance => Participants.Sum(i => i.Power);

        //This describes how this event affects the relationships of the participants.
        public double Grade;    //-1..1
    }

    class Rule_Engine
    {
        //The world that this engine applies its rules
        public World world;

        public Rule_Engine(World w)
        {
            world = w;
            Init_Entities();
        }

        //the default Rulesets.
        public void Init_Entities()
        {

            //justify all entities to approperiate locations.
            foreach (Entity entity in world.Entities)
            {
                //find and then list all neighbours of this entity

            }
        }

        public double Get_Distance(Entity a, Entity b)
        {
            double delta_x = a.Position.X - b.Position.X;
            double delta_y = a.Position.Y - b.Position.Y;
            double delta_z = a.Position.Z - b.Position.Z;
            double Distance = Math.Sqrt(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);
            return Distance;
        }

        public void List_All_Neihgbours(Entity entity, List<Entity> entities)
        {
            //calculate first all the distances and then calculate the average
            double Average = entities.Average(i => Get_Distance(i, entity));

            entity.Environment.Neighbours.AddRange(entities.Where(i => Get_Distance(i, entity) < Average));
        }

        //rules
        public void Justify_Location(Entity entity)
        {
            //Go towards same sized entities-
            //until their perimeters touch each other.

            //Try being inside a bigger entities area-
            //if this entity is twice as small as the bigger entity.

        }
    }
}
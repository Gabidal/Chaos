using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

namespace Chaos
{

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

        public double Get_Ratio(Entity a, Entity b)
        {
            return Math.Max(a.Power, b.Power) / Math.Min(a.Power, b.Power);
        }

        public void List_All_Neihgbours(Entity entity, List<Entity> entities)
        {
            //Calculate first all the distances and then calculate the average
            double Average_Distance = entities.Average(i => Get_Distance(i, entity));

            //If the distance between this and the other entity is less than the average distance then,
            //the other entity is this entity's neighbour.
            entity.Environment.Neighbours.AddRange(entities.Where(i => Get_Distance(i, entity) < Average_Distance).Select(i => new Relation(i)));
        }

        //rules
        public void Justify_Location(Entity entity)
        {
            //Go towards same sized entities-
            //until their perimeters touch each other.
            double Dest_X = 0;
            double Dest_Y = 0;
            double Dest_Z = 0;


            int Skipped_Neighbour_Count = 0;
            foreach (var i in entity.Environment.Neighbours)
            {
                if (!(Get_Ratio(entity, i.Friend) > 1.33 && Get_Ratio(entity, i.Friend) < 2))
                {
                    Skipped_Neighbour_Count++;
                    continue;
                }
                Dest_X += i.Friend.Position.X * i.Relationship;
                Dest_Y += i.Friend.Position.Y * i.Relationship;
                Dest_Z += i.Friend.Position.Z * i.Relationship;
            }

            if (entity.Environment.Neighbours.Count - Skipped_Neighbour_Count == 0)
                return;

            Dest_X /= entity.Environment.Neighbours.Count - Skipped_Neighbour_Count;
            Dest_Y /= entity.Environment.Neighbours.Count - Skipped_Neighbour_Count;
            Dest_Z /= entity.Environment.Neighbours.Count - Skipped_Neighbour_Count;

            double Direction_X = Dest_X - entity.Position.X;
            double Direction_Y = Dest_Y - entity.Position.Y;
            double Direction_Z = Dest_Z - entity.Position.Z;

            double Magnitude = Math.Sqrt(Direction_X * Direction_X + Direction_Y * Direction_Y + Direction_Z * Direction_Z);

            double Distance_X = Direction_X / Magnitude * entity.Speed;
            double Distance_Y = Direction_Y / Magnitude * entity.Speed;
            double Distance_Z = Direction_Z / Magnitude * entity.Speed;

            entity.Position.X += Distance_X;
            entity.Position.Y += Distance_Y;
            entity.Position.Z += Distance_Z;

            

            bool Collides = true;
            while (Collides)
            {
                Collides = false;
                foreach (var i in entity.Environment.Neighbours)
                {
                    if (!(Get_Ratio(entity, i.Friend) < 2))
                    {
                        Skipped_Neighbour_Count++;
                        continue;
                    }

                    Vector Direction = entity.Position - i.Friend.Position;

                    double Safe_Distance = entity.Power + i.Friend.Power;

                    double Direction_Length = Direction.Length;
                    if (Direction_Length < Safe_Distance)
                    {
                        Collides = true;
                        double Penetration_Depth = Safe_Distance - Direction_Length;

                        entity.Position = entity.Position + Direction.Normalized(Direction_Length) * Penetration_Depth;
                    }
                }
            }
        }
    }
}
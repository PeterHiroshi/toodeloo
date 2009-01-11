#ifndef CHIPMUNK_HPP
#define CHIPMUNK_HPP

namespace Chipmunk {
	typedef cpVect Vector2;

	class Space
	{
		public:
			Space();
			~Space();

			Vector2 gravity() const;
			Space& gravity(Vector2 v);

		private:
			cpSpace* _space;
	};

	class Shape;

	class Body
	{
		public:
			Body(float m, float i);
			~Body();

			cpBody* chipmunkBody() { return _body; };
			
			float mass() const;
			float moment() const;
			Vector2 rotation() const;

			Body& mass(float);
			Body& moment(float);
			Body& angle(float);

			Body& slew(Vector2 pos, float dt);
			Body& updateVelocity(Vector2 gravity, float damping, float dt);
			Body& updatePosition(float dt);

			Body& applyImpulse(Vector2, Vector2);
			Body& resetForces();
			Body& applyForce(Vector2, Vector2);

			Body& addShape(Shape shape);

			// Apply a spring force between this and another body at anchors anchr1 and anchr2
			// respectively. k is the spring constant (Young's modulus), rlen is the
			// rest length of the spring, dmp is the damping constant (force/velocity),
			// and dt is the time step to apply the force over. Note: not solving the
			// damping forces in the impulse solver causes problems with large damping values.
			// This function will eventually be replaced by a new constraint (joint) type.
			Body& dampedSpring(Body& other, Vector2 anchr1, Vector2 anchr2, float rlen, float k, float dmp, float dt);

		private:
			cpBody* _body;
			std::vector<Shape> _shapes;
	};

		class Shape
		{
			public:
				struct ShapeWrapper
				{
					ShapeWrapper(cpShape* shape)
					{
						p = shape;
					};
					
					~ShapeWrapper()
					{
					cpShapeDestroy(p);
					cpShapeFree(p);
					}

					cpShape* p;
				};

				Shape(boost::shared_ptr<ShapeWrapper> shape_wrapper);
				Shape(cpShape* shape);

				static Shape circle(Body& body, float radius, Vector2 offset);
				static Shape polygon(Body& body, std::vector<Vector2> vertices, Vector2 offset);
				static Shape segment(Body& body, Vector2 a, Vector2 b, float radius);

			private:
				boost::shared_ptr<ShapeWrapper> _shape_wrapper;
	};
}

#endif

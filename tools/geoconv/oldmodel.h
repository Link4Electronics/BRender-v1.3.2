#define br_edge br_uint_8

typedef struct old_face {
	br_uint_16 vertices[3];		/* Vertices around face 				*/
	br_uint_16 edges[3];		/* Edges around face					*/
	br_material *material;		/* Face material (or NULL) 				*/
	br_uint_16 smoothing;		/* Controls if shared edges are smooth	*/
	br_uint_8 flags;			/* Bits 0,1 and 2 denote internal edges	*/
	br_uint_8 _pad0;
	br_fvector3 n;				/* Plane equation of face				*/
	br_scalar d;
} old_face;

typedef struct br_face_group {
	br_material *material;		/* Group material (or NULL) 			*/
	br_face *faces;				/* faces in group						*/
	br_uint_16 nfaces;			/* Number of faces in a group			*/
} br_face_group;

typedef struct br_vertex_group {
	br_material *material;		/* Group material (or NULL) 			*/
	br_vertex *vertices;		/* vertices in group					*/
	br_uint_16 nvertices;		/* Number of vertices in a group		*/
} br_vertex_group;

typedef struct old_model {
	char *identifier;

	br_vertex *vertices;
        old_face *faces;

	br_uint_16 nvertices;
	br_uint_16 nfaces;

	/*
	 * Offset of model's pivot point (where it attaches to parent)
	 */
	br_vector3 pivot;

	/*
	 * Flags describing what is allowed in ModelPrepare()
	 */
	br_uint_16 flags;

	/*
	 * Application call
	 */
	br_model_custom_cbfn *custom;

	/*
	 * Application defined data - untouched by system
	 */
	void *user;

	/*
	 * Generated by ModelUpdate
	 */
	/*
	 * Bounding radius of model from origin
	 */
	br_scalar radius;

	/*
	 * Axis-aligned box that bound model in model coords
	 */
	br_bounds bounds;

	/*
	 * Vertices and faces that have been sorted
	 * into groups, removing conflicts at material boundaries
	 * and smoothign groups
	 */
	br_uint_16 nprepared_vertices;
	br_uint_16 nprepared_faces;

	br_face *prepared_faces;
	br_vertex *prepared_vertices;

	/*
	 * Groups of faces and vertices, by material
	 */
	br_uint_16 nface_groups;
	br_uint_16 nvertex_groups;

	br_face_group *face_groups;
	br_vertex_group *vertex_groups;

	/*
	 * Upper limit on the face->edges[] entries
	 */
	br_uint_16 nedges;

	/*
	 * Pointers to tables that map prepared face and vertex indexes
	 * back to original face index
	 *
	 * Only generated if BR_MODF_GENERATE_TAGS is set
	 */
	br_uint_16 *face_tags;
	br_uint_16 *vertex_tags;

	/*
	 * Private fields
	 */
	br_uint_32 prep_flags;
	br_uint_16 *smooth_strings;
	void *rptr;
} old_model;


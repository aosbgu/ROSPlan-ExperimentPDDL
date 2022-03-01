(define (domain experiment_domain)
	(:requirements :strips :typing :fluents :disjunctive-preconditions :durative-actions)


	(:types
		;; text displayed to the user
		discrete_location outer_elv_button robot objects
	)


	(:predicates
	(can_act)
		(object_at ?o - objects ?l - discrete_location)
		(connected ?c1 - discrete_location ?c2 - discrete_location)
		(possible_location ?o - objects ?l - discrete_location)
		(near ?r - robot ?l - discrete_location)
		(hand_empty ?r - robot)
		(door_is_open ?l - discrete_location)
		(buttton_associated ?b - outer_elv_button ?l - discrete_location)
		(is_elevator ?l - discrete_location)
		(pickable ?o - objects)
		(holding ?r - robot ?o - objects)
	)
	
	(:durative-action pick_unknown
		:parameters (?r - robot ?o - objects ?l - discrete_location)
		:duration ( = ?duration 1)
	:condition (and

(at start (can_act))
				(at start (hand_empty ?r))
				(at start (object_at ?o ?l))
				(at start (near ?r ?l))
				(at start (pickable ?o))
			)
		:effect (and
			(at start (not (object_at ?o ?l)))
(at start (not (can_act)))
(at end (can_act))
			(at start (not (hand_empty ?r)))
			(at start (holding ?r ?o))
			)
	)

	(:durative-action place_unknown
		:parameters (?r - robot ?o1 - objects ?o2 - objects ?l - discrete_location)
		:duration ( = ?duration 1)
	:condition (and
(at start (can_act))
			(at start (holding ?r ?o1))
			(at start (object_at ?o2 ?l))
			(at start (near ?r ?l))
			)
		:effect (and
(at start (not (can_act)))
(at end (can_act))
			(at start (not (holding ?r ?o1)))
			(at start (object_at ?o1 ?l))
			(at start (hand_empty ?r))
			)
	)
	(:durative-action robot_navigation
		:parameters (?r - robot ?l1 - discrete_location ?l2 - discrete_location)
		:duration ( = ?duration 1)
	:condition (and
(at start (can_act))
			(at start (near ?r ?l1))
				
				(at start (connected ?l1 ?l2))
				
	)
		:effect (and
(at start (not (can_act)))
(at end (can_act))
			(at start (not (near ?r ?l1)))
			(at start (near ?r ?l2))
			(at start (hand_empty ?r))
			)
	)
	(:durative-action sense_object
		:parameters (?r - robot ?o - objects ?l - discrete_location)
		:duration ( = ?duration 1)
	:condition (and
(at start (can_act))
			(at start (near ?r ?l))
			(at start (possible_location ?o ?l))	
			)
		:effect (and
(at start (not (can_act)))
(at end (can_act))
		 (at start (object_at ?o ?l))
)
	)

)




(define (domain experiment_domain)
	(:requirements :strips :typing :disjunctive-preconditions)


	(:types
		;; text displayed to the user
		discrete_location outer_elv_button robot objects
	)


	(:predicates
	
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
	
	(:action pick_unknown
		:parameters (?r - robot ?o - objects ?l - discrete_location)
		:precondition (and
				(hand_empty ?r)
				(object_at ?o ?l)
				(near ?r ?l)
				(pickable ?o)
			)
		:effect (and
			(not (object_at ?o ?l))
			(not (hand_empty ?r))
			(holding ?r ?o)
			)
	)

	(:action place_unknown
		:parameters (?r - robot ?o1 - objects ?o2 - objects ?l - discrete_location)
		:precondition (and
			(holding ?r ?o1)
			(object_at ?o2 ?l)
			(near ?r ?l)
			)
		:effect (and
			(not (holding ?r ?o1))
			(object_at ?o1 ?l)
			(hand_empty ?r)
			)
	)
	(:action robot_navigation
		:parameters (?r - robot ?l1 - discrete_location ?l2 - discrete_location)
		:precondition (and
			(near ?r ?l1)
				(or
				(connected ?l1 ?l2)
				(connected ?l2 ?l1)
				)
	)
		:effect (and
			(not (near ?r ?l1))
			(near ?r ?l2)
			(hand_empty ?r)
			)
	)
	(:action sense_object
		:parameters (?r - robot ?o - objects ?l - discrete_location)
		:precondition (and
			(near ?r ?l)
			(possible_location ?o ?l)	
			)
		:observe (object_at ?o ?l)
	)

)




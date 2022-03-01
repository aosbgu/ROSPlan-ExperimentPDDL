(define (problem experiment_problem) 
(:domain experiment_domain) 
(:objects
lab211 outside_lab211 auditorium corridor near_elevator1 open_area corner_area elevator1 - discrete_location
up down - outer_elv_button
armadillo - robot
can table1 table2 table3 table4 - objects)


		
(:init 
(possible_location can corridor)
(possible_location can outside_lab211)
(hand_empty armadillo)
(pickable can)
(near armadillo near_elevator1)
(object_at table1 corridor)
(object_at table2 lab211)
(object_at table3 auditorium)
(object_at table4 outside_lab211) 

(unknown (object_at can corridor))
	(unknown(object_at can outside_lab211))
(oneof
         (object_at can corridor)
         (object_at can outside_lab211)
	)



(buttton_associated up near_elevator1)
(is_elevator elevator1)
(connected open_area near_elevator1)
(connected open_area auditorium)
(connected open_area corridor)
(connected open_area corner_area)
(connected corner_area outside_lab211)
(connected lab211 outside_lab211)
(connected corner_area auditorium)
(connected corner_area corridor)
(connected corner_area near_elevator1)
(connected near_elevator1 corridor)
(connected near_elevator1 auditorium)
(connected auditorium corridor)
(connected near_elevator1 elevator1)
)

(:goal (and
(near armadillo near_elevator1)
(object_at can auditorium)
)))

SELECT name
FROM people JOIN stars ON stars.person_id = people.id JOIN movies ON movies.id = stars.movie_id
WHERE name = 'Kevin Bacon' AND birth = '1958'
INTERSECT
SELECT name
FROM people JOIN stars ON stars.person_id = people.id JOIN movies ON movies.id = stars.movie_id
GROUP BY movie_id;
SELECT title
FROM movies
WHERE id IN
(SELECT movie_id
FROM stars
WHERE person_id =
(SELECT COUNT(id)
FROM people
WHERE name IN ('Helena Bonham Carter'))
AND person_id =
(SELECT COUNT(id)
FROM people
WHERE name IN ('Johnny Depp')));
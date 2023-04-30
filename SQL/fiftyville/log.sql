-- Keep a log of any SQL queries you execute as you solve the mystery.

-- SELECT *
-- FROM crime_scene_reports
-- WHERE street = 'Humphrey Street';

--CRIME: 295 | 2021 | 7     | 28  | Humphrey Street |
-- Theft of the CS50 duck took place at 10:15am at the
-- Humphrey Street bakery. Interviews were conducted today
-- with three witnesses who were present at the time –
-- each of their interview transcripts mentions the bakery.

-- SELECT *
-- FROM interviews
-- WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%';

-- | 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft,
--  I saw the thief get into a car in the bakery parking lot and drive away.
--  If you have security footage from the bakery parking lot, you might want to
--  look for cars that left the parking lot in that time frame.                                                          |
-- | 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name,
--  but it was someone I recognized. Earlier this morning, before I arrived
--  at Emma's bakery, I was walking by the ATM on Leggett Street and saw the
--  thief there withdrawing some money.                                                                                                 |
-- | 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery,
-- they called someone who talked to them for less than a minute. In the call,
-- I heard the thief say that they were planning to take the earliest flight out
-- of Fiftyville tomorrow. The thief then asked the person on the other end of
-- the phone to purchase the flight ticket. |

-- TRAIL 1 (RUTH INTERVIEW):

-- SELECT name
-- FROM people
-- WHERE license_plate IN
-- (SELECT license_plate
-- FROM bakery_security_logs
-- WHERE year = 2021 AND month = 7 AND day = 28
-- AND hour = 10 AND minute BETWEEN 15 AND 25);

-- +---------+
-- |  name   |
-- +---------+
-- | Vanessa |
-- | Barry   |
-- | Iman    |
-- | Sofia   |
-- | Luca    |
-- | Diana   |
-- | Kelsey  |
-- | Bruce   |
-- +---------+

-- TRAIL 2 (EUGENE INTERVIEW):

-- When did Eugene arrive at bakery?
-- SELECT name,license_plate
-- FROM people
-- WHERE name LIKE '%Eugene%';

-- +--------+---------------+
-- |  name  | license_plate |
-- +--------+---------------+
-- | Eugene | 47592FJ       |
-- +--------+---------------+

-- Eugene didn't drive to the bakery...
-- So get names of people that withdrew that morning:
-- SELECT name
-- FROM people
-- WHERE id IN
-- (SELECT person_id
-- FROM bank_accounts
-- WHERE account_number IN
-- (SELECT account_number
-- FROM atm_transactions
-- WHERE year = 2021 AND month = 7 AND day = 28
-- AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'));

-- +---------+
-- |  name   |
-- +---------+
-- | Kenny   |
-- | Iman    |
-- | Benista |
-- | Taylor  |
-- | Brooke  |
-- | Luca    |
-- | Diana   |
-- | Bruce   |
-- +---------+

-- Combining trail 1 and 2:
-- SELECT name
-- FROM people
-- WHERE license_plate IN
-- (SELECT license_plate
-- FROM bakery_security_logs
-- WHERE year = 2021 AND month = 7 AND day = 28
-- AND hour = 10 AND minute BETWEEN 15 AND 25)
-- AND id IN
-- (SELECT person_id
-- FROM bank_accounts
-- WHERE account_number IN
-- (SELECT account_number
-- FROM atm_transactions
-- WHERE year = 2021 AND month = 7 AND day = 28
-- AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'));

-- TRAIL 3 (RAYMOND INTERVIEW):

-- SELECT name
-- FROM people
-- WHERE phone_number IN
-- (SELECT caller
-- FROM phone_calls
-- WHERE year = 2021 AND month = 7 AND day = 28
-- AND duration between 0 and 60);

-- COMBINE ALL 3 TRAILS:

-- SELECT name
-- FROM people
-- WHERE license_plate IN
--     (SELECT license_plate
--     FROM bakery_security_logs
--     WHERE year = 2021 AND month = 7 AND day = 28
--     AND hour = 10 AND minute BETWEEN 15 AND 25)
-- AND id IN
--     (SELECT person_id
--     FROM bank_accounts
--     WHERE account_number IN
--     (SELECT account_number
--     FROM atm_transactions
--     WHERE year = 2021 AND month = 7 AND day = 28
--     AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'))
-- AND name IN
--     (SELECT name
--     FROM people
--     WHERE phone_number IN
--     (SELECT caller
--     FROM phone_calls
--     WHERE year = 2021 AND month = 7 AND day = 28
--     AND duration between 0 and 60));

-- +-------+
-- | name  |
-- +-------+
-- | Diana |
-- | Bruce |
-- +-------+

-- TRAIL 4: GET NAMES OF PEOPLE ON EARLIEST FLIGHT
-- SELECT name
-- FROM people
-- WHERE passport_number IN
-- (SELECT passport_number
-- FROM passengers
-- WHERE flight_id =
-- (SELECT id
-- FROM flights
-- WHERE year = 2021 AND month = 7 AND day = 29
-- ORDER BY hour
-- LIMIT 1));

-- CROSS-REF ALL 4 TRAILS TO FIND THIEF:

-- SELECT name
-- FROM people
-- WHERE license_plate IN
--     (SELECT license_plate
--     FROM bakery_security_logs
--     WHERE year = 2021 AND month = 7 AND day = 28
--     AND hour = 10 AND minute BETWEEN 15 AND 25)
-- AND id IN
--     (SELECT person_id
--     FROM bank_accounts
--     WHERE account_number IN
--     (SELECT account_number
--     FROM atm_transactions
--     WHERE year = 2021 AND month = 7 AND day = 28
--     AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'))
-- AND name IN
--     (SELECT name
--     FROM people
--     WHERE phone_number IN
--     (SELECT caller
--     FROM phone_calls
--     WHERE year = 2021 AND month = 7 AND day = 28
--     AND duration between 0 and 60))
-- AND name IN
--     (SELECT name
--     FROM people
--     WHERE passport_number IN
--     (SELECT passport_number
--     FROM passengers
--     WHERE flight_id =
--     (SELECT id
--     FROM flights
--     WHERE year = 2021 AND month = 7 AND day = 29
--     ORDER BY hour
--     LIMIT 1)));

-- +-------+
-- | name  |
-- +-------+
-- | Bruce |
-- +-------+

-- City the thief escaped to:
-- SELECT city
-- FROM airports
-- WHERE id =
-- (SELECT destination_airport_id
-- FROM flights
-- WHERE year = 2021 AND month = 7 AND day = 29
-- ORDER BY hour
-- LIMIT 1);

-- +---------------+
-- |     city      |
-- +---------------+
-- | New York City |
-- +---------------+

-- Accomplice:

-- SELECT name
-- FROM people
-- WHERE phone_number IN
--     (SELECT receiver
--     FROM phone_calls
--     WHERE year = 2021 AND month = 7 AND day = 28
--     AND duration between 0 and 60
--     AND caller =
--         (SELECT phone_number
--         FROM people
--         WHERE name = 'Bruce'));

-- +-------+
-- | name  |
-- +-------+
-- | Robin |
-- +-------+
use First_Base
CREATE LOGIN Andrey WITH PASSWORD='password'
CREATE USER AndreyUser FOR LOGIN Andrey
GRANT SELECT ON dbo.Material TO AndreyUser
GRANT SELECT ON dbo.Usluga TO AndreyUser;


create procedure dbo.InsertInsurance

@Policy_ int,
@Expiry date,
@Location_ varchar(10),
@State_ varchar(10),
@Region varchar(10),
@InsuredValue float,
@Construction varchar(10),
@BusinessType varchar(10),
@Earthquake varchar(10),
@Flood varchar(10)
AS

Begin

Insert into dbinsurance (Policy_,Expiry,Location_,State_,Region,InsuredValue,Construction,BusinessType,Earthquake,Flood)
Values(@Policy_,@Expiry,@Location_,@State_,@Region,@InsuredValue,@Construction,@BusinessType,@Earthquake,@Flood)

end



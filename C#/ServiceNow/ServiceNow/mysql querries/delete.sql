USE [insurance]
GO
/****** Object:  StoredProcedure [dbo].[DeleteInsurance]    Script Date: 10/1/2022 12:14:56 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
ALTER procedure [dbo].[DeleteInsurance]
as
truncate table [insurance].[dbo].[dbinsurance]

using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using ExcelDataReader;
using System.Data.SqlClient;
using System.Data;
using System.Net.Mail;
using System.Net;

namespace ServiceNow
{
    internal class Program
    {
        public static int East = 0;
        public static int Midwest = 0;
        public static int Northeast = 0;
        public static int Central = 0;
        public static double total_insured_value = 0;
        public static string total_insured_values;
        static void Main(string[] args)
        {
            File.AppendAllText(@"C:\cucc\Projekt\C#\ServiceNow\Logs\logs.txt", "\n" + DateTime.Now.ToString("MM/dd/yyyy HH:mm:ss") + Environment.NewLine + "\n");

            StartProgram();
        }

        private static void StartProgram()
        {
            Console.ReadKey();
            DeleteInsurance();
            Console.ReadKey();
            InsertInsurance();
            //File.AppendAllText(@"C:\cucc\Projekt\C#\ServiceNow\Logs\logs.txt", "\n" + DateTime.Now.ToString("MM/dd/yyyy HH:mm:ss") + Environment.NewLine + "\n");
            total_insured_values = DoubleToString();
            SendMail();
            Console.ReadKey();
        }

        private static string DoubleToString()
        {
            double i = total_insured_value;
            string s = i.ToString("#,#").Replace(',', ' ');
            return s;
        }
        #region InsertInsurance

        private static void InsertInsurance()
        {
            List<insuranceEntities> listInsurance = new List<insuranceEntities>();
            try
            {
                listInsurance = getInsuranceFromXlsx(@"C:\cucc\Projekt\C#\ServiceNow\Input\sampledatainsurance.xlsx");
                Console.WriteLine(" Nr. lines: " + listInsurance.Count());
                File.AppendAllText(@"C:\cucc\Projekt\C#\ServiceNow\Logs\logs.txt", "\n" + "Nr. lines: " + listInsurance.Count());
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception getInsuranceFromXlsx: " + ex);
                Console.WriteLine(ex.Message);
                LogWrite(ex.ToString());
            }

            if (listInsurance.Count > 0)

            {
                try
                {
                    Console.WriteLine("\nRead succesfully");
                    LogWrite("Read Succesfully".ToString());
                    Console.WriteLine("\nInserting to the database");
                    LogWrite("Inserting to the database".ToString());                  
                    StoredProceduresInsertInsurance(listInsurance);
                    Console.WriteLine("\nSuccesfull insertion");
                    LogWrite("Succesfull insertion".ToString());
                }

                catch (Exception ex)

                {
                    LogWrite(ex.ToString());
                    Console.WriteLine("\nUnsuccesfull reading");
                    Console.WriteLine("Exception getInsuranceFromXlsx: " + ex);
                }
            }
        }
        #endregion

        #region getInsuranceFromXlsx

        private static List<insuranceEntities> getInsuranceFromXlsx(string filePath)
        {          
            var p = 0;         
            var listObj = new List<insuranceEntities>();
            try

            {
                using (var stream = File.Open(filePath, FileMode.Open, FileAccess.Read))
                {
                    using (var reader = ExcelReaderFactory.CreateReader(stream))
                    {
                        do
                        {
                            while (reader.Read())
                            {
                                var obj = new insuranceEntities();
                                var lineExtract = reader;
                                var lineV = lineExtract;
                                p++;
                                if ((String)reader[0] != "Policy")
                                {
                                    obj.Policy = (string)reader[0];
                                    //Console.WriteLine(reader[0]);
                                    obj.Expiry = (Nullable<System.DateTime>)reader[1];
                                    //Console.WriteLine(reader[1]);
                                    obj.Location = (String)reader[2];
                                    //Console.WriteLine(reader[2]);
                                    obj.State = (String)reader[3]; 
                                    //Console.WriteLine(reader[3]);
                                    obj.Region = (String)reader[4];
                                    if ((string)reader[4] == "East")
                                        East++;
                                    else if ((string)reader[4] == "Midwest")
                                        Midwest++;
                                    else if ((string)reader[4] == "Northeast")
                                        Northeast++;
                                    else if ((string)reader[4] == "Central")
                                        Central++;
                                    obj.InsuredValue = (Nullable<System.Double>)reader[5];
                                    total_insured_value = (double)(total_insured_value + (double?)reader[5]);                                 
                                    obj.Construction = (String)reader[6];
                                    //Console.WriteLine(reader[6]);
                                    obj.BusinessType = (String)reader[7];
                                    //Console.WriteLine(reader[7]);
                                    obj.Earthquake = (String)reader[8];
                                    //Console.WriteLine(reader[8]);
                                    obj.Flood = (String)reader[9];
                                    //Console.WriteLine(reader[9]);
                                    listObj.Add(obj);
                                }
                                else
                                {
                                    Console.WriteLine("Insurance.xlsx : " + lineV[0] + "  " + lineV[1] + " " + p + " ");
                                }                             
                            }
                        } while (reader.NextResult());
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("\nUnsuccesfull reading");
                Console.WriteLine("Exception: " + ex);
                LogWrite(ex.ToString());
            }
            //MoveFileInsurance(filePath);       
            return listObj;
        }
        #endregion

        #region MoveFile
     
        private static void MoveFileInsurance(string filePath)
        {
            string fileDest = @"D:\projects\C#\ServiceNow\Output\sampledatainsurance.xlsx";
            try

            {
                // Check if file exists with its full path   
                if (File.Exists(fileDest))
                {
                    // If file found, delete it    
                    File.Delete(fileDest);
                    Console.WriteLine("The sampledatainsurance.xlsx file already exists in the Output and will be deleted.");
                    File.AppendAllText(@"C:\cucc\Projekt\C#\ServiceNow\Logs\logs.txt", "\n\t" + fileDest + "File deleted" + Environment.NewLine);
                }
            }

            catch (IOException ioExp)

            {
                Console.WriteLine(ioExp.Message);
                File.AppendAllText(@"C:\cucc\Projekt\C#\ServiceNow\Logs\logs.txt", "\n\t" + ioExp.Message + Environment.NewLine);
            }

            try

            {
                File.Move(filePath, fileDest);
                Console.WriteLine("{0} was moved to {1}.", filePath, fileDest);
                File.AppendAllText(@"C:\cucc\Projekt\C#\ServiceNow\Logs\logs.txt", "\n\t" + fileDest + " was moved to " + filePath + Environment.NewLine + "\n");
            }
            catch (IOException iox)
            {
                Console.WriteLine(iox.Message);
                LogWrite(iox.ToString());
            }
        }
        #endregion

        private static void LogWrite(String ax)
        {
            File.AppendAllText(@"C:\cucc\Projekt\C#\ServiceNow\Logs\logs.txt", "\n\t" + ax + Environment.NewLine);
        }     
        #region Mail

        private static void SendMail()
        {
            string fromMail = "servicenowmailsender@gmail.com";
            string fromPassword = "lrfvhgljsfshrxde";

            MailMessage message = new MailMessage();
            message.From = new MailAddress(fromMail);
            message.Subject = "Test Subject";
            message.To.Add(new MailAddress("servicenowmailsender@gmail.com"));
            message.Body = "<h3> Hello Team <br>  </h3>"

                + DateTime.Now.ToString("MM / dd / yyyy HH: mm: ss") + "<br>" +

                "<h5 style='color: darkgrey; font - size:40px;font-family:arial;'> INSURANCE: <br></h5><span style='color: grey; font - size:11px; '> " +

                "<span> -<b>" + total_insured_values + 
                "</b></span><span style='color: grey; font - size:11px; '> $ is the total insured value.  <span style='background-color:lightgreen;color: black;'>(GOOD)</span></span><br>" +

                

                "<span>-<b>" + East +
                "</b></span><span style='color: grey; font - size:11px; '> is the number of insurances in the Eastern region.  <span style='background-color:lightgreen;color: black;'>(GOOD)</span></span><br>" +

                "<span>-<b>" + Central +
                "</b></span><span style='color: grey; font - size:11px; '> is the number of insurances in the Central region.  <span style = 'background-color:red;color: white;' >(BAD)</span><br>" +

                "<span>-<b>" + Midwest +
                "</b></span><span style='color: grey; font - size:11px; '> is the number of insurances in the Midwestern region.  <span style='background-color:orange;color: black;'>(AVG)</span></span><br>" +

                "<span>-<b>" + Northeast +
                "</b></span><span style='color: grey; font - size:11px; '> is the number of insurances in the Northeastern region.  <span style = 'background-color:red;color: white;' >(BAD)</span><br>";
                         
            message.IsBodyHtml = true;
            var smptClient = new SmtpClient("smtp.gmail.com")
            {
                Port = 587,
                    Credentials = new NetworkCredential(fromMail, fromPassword),
                    EnableSsl = true,
            };
            smptClient.Send(message);
            Console.WriteLine("Email sent");        
        }
        #endregion

        private static void StoredProceduresInsertInsurance(List<insuranceEntities> listInsurance)
        {
            foreach (var insurance in listInsurance)
            {
                string connectionString = @"Data Source=localhost\SQLEXPRESS01;" +
                              "Initial Catalog=insurance;Integrated Security=TRUE";
                string SQL = "InsertInsurance";
                // Create ADO.NET objects.
                SqlConnection con = new SqlConnection(connectionString);
                SqlCommand com = new SqlCommand(SQL, con);
                com.CommandType = CommandType.StoredProcedure;

                com.Parameters.Add("@Policy_", SqlDbType.VarChar).Value = insurance.Policy;

                com.Parameters.Add("@Expiry", SqlDbType.VarChar).Value = insurance.Expiry;

                com.Parameters.Add("@Location_", SqlDbType.VarChar).Value = insurance.Location;

                com.Parameters.Add("@State_", SqlDbType.VarChar).Value = insurance.State;

                com.Parameters.Add("@Region", SqlDbType.VarChar).Value = insurance.Region;

                com.Parameters.Add("@InsuredValue", SqlDbType.VarChar).Value = insurance.InsuredValue;

                com.Parameters.Add("@Construction", SqlDbType.VarChar).Value = insurance.Construction;

                com.Parameters.Add("@BusinessType", SqlDbType.VarChar).Value = insurance.BusinessType;

                com.Parameters.Add("@Earthquake", SqlDbType.VarChar).Value = insurance.Earthquake;

                com.Parameters.Add("@Flood", SqlDbType.VarChar).Value = insurance.Flood;
              
                con.Open();
                com.ExecuteNonQuery();
                con.Close();
            }
        }
        private static void DeleteInsurance()
        {
            string connectionString = @"Data Source=localhost\SQLEXPRESS01;" +
                               "Initial Catalog=insurance;Integrated Security=TRUE";
            string SQL = "DeleteInsurance";
            // Create ADO.NET objects.
            SqlConnection con = new SqlConnection(connectionString);
            SqlCommand cmd = new SqlCommand(SQL, con);
            cmd.CommandType = CommandType.StoredProcedure;
            // Execute the command.
            con.Open();
            int rowsAffected = cmd.ExecuteNonQuery();
            con.Close();
            // Display the result of the operation.
            Console.WriteLine("Database succesfully deleted!");
        }
    }
}


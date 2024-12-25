namespace Day04
{
    public class BookFunctions
    {
        public static string GetTitle(Book B)
        {
            return B.Title;
        }
        public static string GetAuthors(Book B)
        {
            if (B.Authors == null || B.Authors.Length == 0)
            {
                return "No authors available.";
            }

            string authors = "";
            foreach (string author in B.Authors)
            {
                authors += $"{author}, ";
            }
            return authors.TrimEnd(',', ' ');
        }
        public static string GetPrice(Book B)
        {
            return B.Price.ToString();
        }
    }
}

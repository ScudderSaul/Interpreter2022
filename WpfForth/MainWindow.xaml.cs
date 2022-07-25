using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using Microsoft.Win32;

using ClrWrapper;
using WpfForth.Annotations;

namespace WpfForth
{


    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        ManagedLanguage languageforth;
        private ObservableCollection<string> _stackedWork;
        private string Prompt = "F> ";

        public MainWindow()
        {
            InitializeComponent();
            Loaded += MainWindow_Loaded;
        }

        void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            this.DataContext = this;
            StackedWork = new ObservableCollection<String>();
            CreateInputBlock();
            BothDoc.Blocks.Add(currentInput);

            this.InvalidateArrange();
            languageforth = new ManagedLanguage();
        }

        Paragraph currentInput { get; set; }

        Paragraph currentOutput { get; set; }

        Paragraph currentTrace{ get; set; }
        
        public void CreateInputBlock()
        {
            Paragraph paragraph = new Paragraph();
            paragraph.FontSize = 12;
            paragraph.Foreground = new SolidColorBrush(Colors.Black);
            paragraph.Margin = new Thickness(1.0);
            paragraph.Background = new SolidColorBrush(Colors.WhiteSmoke);
            paragraph.TextIndent = 0.0;
            paragraph.Inlines.Add(new Run(Prompt));
            currentInput = paragraph;
        }

        public void CreateOutputBlock()
        {
            Paragraph paragraph = new Paragraph();
            paragraph.FontSize = 12;
            paragraph.Foreground = new SolidColorBrush(Colors.DarkBlue);
            paragraph.Margin = new Thickness(1.0);
            paragraph.Background = new SolidColorBrush(Colors.WhiteSmoke);
            paragraph.TextIndent = 0.0;
            paragraph.Inlines.Add(new Run(string.Empty));
            paragraph.BorderBrush = new SolidColorBrush(Colors.DarkBlue);
            paragraph.BorderThickness = new Thickness(0,1,0,1);
            currentOutput = paragraph;
        }

        public void CreateTraceBlock()
        {
            Paragraph paragraph = new Paragraph();
            paragraph.FontSize = 12;
            paragraph.Foreground = new SolidColorBrush(Colors.DarkOliveGreen);
            paragraph.Margin = new Thickness(1.0);
            paragraph.Background = new SolidColorBrush(Colors.WhiteSmoke);
            paragraph.TextIndent = 0.0;
            paragraph.BorderBrush = new SolidColorBrush(Colors.DarkGoldenrod);
            paragraph.BorderThickness = new Thickness(1);
            paragraph.Inlines.Add(new Run(string.Empty));
            currentTrace = paragraph;
        }


        public ObservableCollection<string> StackedWork
        {
            get { return _stackedWork; }
            set
            {
                _stackedWork = value;
                OnPropertyChanged();
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }

        private void InterpretButton_OnClick(object sender, RoutedEventArgs e)
        {
            string st = string.Empty;

            CreateOutputBlock();
            CreateTraceBlock();

            var cc = from rr in currentInput.Inlines
                     where rr is Run
                     select rr;

            foreach (var xx in cc)
            {
                st += (xx as Run).Text;
            }
            st = st.Remove(0, 2);

            languageforth.Input(st);
            
            bool done = false;
           
            while (done == false)
            {
                string str = languageforth.GetOut();
                (currentOutput.Inlines.First() as Run).Text += str;
                done = languageforth.DoneOut();
            }
            OutDoc.Blocks.Add(currentOutput);
            done = false;
            this.InvalidateArrange();

            while (done == false)
            {
                string str = languageforth.GetTrace();
                (currentTrace.Inlines.First() as Run).Text += str;
                done = languageforth.DoneTrace();
            }

            TraceDoc.Blocks.Add(currentTrace);
            this.InvalidateArrange();

            CreateInputBlock();
            BothDoc.Blocks.Add(currentInput);
            this.InvalidateArrange();
            
        }

        private void FileButton_OnClick(object sender, RoutedEventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.DefaultExt = ".4th";
            dlg.Multiselect = false;
            dlg.Title = "Forth (.4th) Files";
            string buffer = string.Empty;

            if (dlg.ShowDialog() == true)
            {
                try
                {
                  
                   if( File.Exists(dlg.FileName) == true)
                    {
                       StreamReader reader = new StreamReader(dlg.FileName);
                       string str = string.Empty;
                       while ((str = reader.ReadLine()) != null)
                       {
                           buffer += (str + "\n\r");
                       }
                       (currentInput.Inlines.First() as Run).Text += (" " + buffer);
                        this.InvalidateArrange();
                    }
                }
                catch (Exception ee)
                {
                    MessageBox.Show(ee.Message);
                }

                
            }
        }
    }
}

#echo "Downloading gc-7.2.tar.gz"
#wget http://www.hpl.hp.com/personal/Hans_Boehm/gc/gc_source/gc-7.2.tar.gz
mkdir usr
echo "Downloading gmp-5.0.5.tar.bz"
wget ftp://ftp.gnu.org/gnu/gmp/gmp-5.0.5.tar.bz2
bzip2 -d gmp-5.0.5.tar.bz2
tar xf gmp-5.0.5.tar
cd gmp-5.0.5
echo "Configuring gmp-5.0.5"
./configure --prefix=../usr
echo "Making gmp-5.0.5"
make -j 8
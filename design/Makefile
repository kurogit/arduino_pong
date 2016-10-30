PP=/opt/pp/pp
PANDOC=pandoc

TMPDIR=/tmp
BASEDIR=$(CURDIR)
INPUTDIR=$(BASEDIR)/source
OUTPUTDIR=$(BASEDIR)

MERGEDFILE=merged.md
OUTPUTNAME=arduino_pong_design.md

.PHONY: all
all: pandoc

.PHONY: pp
pp:
	$(PP) -en "$(INPUTDIR)"/*.md > "$(TMPDIR)/$(MERGEDFILE)"

.PHONY: pandoc
pandoc: trim
	$(PANDOC) "$(TMPDIR)/$(MERGEDFILE)" \
		--verbose \
		--smart \
		--standalone \
		-N \
		--toc \
		--template "$(INPUTDIR)/template.markdown_github" \
		--from markdown \
		--to markdown_github \
		--output "$(OUTPUTDIR)/$(OUTPUTNAME)"

.PHONY: trim
trim: pp
	for a in source/figures/gen/*.png; do convert -trim "$$a" "$$a"; done
